#include "Usb.h"

#include "BinaryBufferSerializer.h"
#include "UsbBuffer.h"
#include "usbd_cdc_if.h"

static Brytec::UsbBuffer s_sendBuffer;

void Usb::send(Brytec::CanExtFrame& frame)
{
    Brytec::UsbPacket packet;
    packet.set<Brytec::CanExtFrame>(frame);
    s_sendBuffer.add(packet);
}

void Usb::send(Brytec::UsbPacket& packet)
{
    s_sendBuffer.add(packet);
}

extern USBD_HandleTypeDef hUsbDeviceFS;

void Usb::update()
{

    // Send
    {
        static uint8_t rawSend[64];
        USBD_CDC_HandleTypeDef* hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
        // Test if the USB CDC is ready to transmit
        if (hcdc->TxState == 0 && s_sendBuffer.size() > 0) {
            Brytec::UsbPacket sendPacket = s_sendBuffer.get();
            rawSend[0] = Brytec::PacketStart;
            rawSend[1] = sendPacket.length;
            memcpy(&rawSend[2], sendPacket.data, sendPacket.length + 2);
            USBD_CDC_SetTxBuffer(&hUsbDeviceFS, rawSend, sendPacket.length + 2);
            USBD_CDC_TransmitPacket(&hUsbDeviceFS);
            printf("tx data: %d", sendPacket.data[6]);
        }
    }

    // Receive
    {
        static uint8_t rxBuffer[APP_RX_DATA_SIZE];
        if (CDC_Rx_Data_Lenth() > 14) {
            // We have data
            uint32_t dataLength = CDC_Get_Received_Data_FS(rxBuffer);

            uint32_t i = 0;
            while (i < dataLength) {
                if (rxBuffer[i] == Brytec::PacketStart && (dataLength - i) > 3) {

                    Brytec::UsbPacket packet;
                    packet.length = rxBuffer[i + 1];
                    if (packet.length <= 62 && (dataLength - i - packet.length) >= 0) {
                        memcpy(packet.data, &rxBuffer[i + 2], packet.length);
                        i += (2 + packet.length);
                        // Valid packet, do something with it
                        printf("rx data: %d", packet.data[6]);
                        send(packet);
                    } else {
                        i++;
                    }

                } else {
                    i++;
                }
            }
        }
    }
}