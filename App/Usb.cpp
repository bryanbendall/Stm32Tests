#include "Usb.h"

#include "BinaryBufferSerializer.h"
#include "UsbBuffer.h"
#include "usbd_cdc_if.h"

extern uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];
extern uint32_t RxDataLenth;

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
    }

    static uint8_t rxBuffer[64];
    if (RxDataLenth) {
        // We have data
        CDC_Get_Received_Data_FS(rxBuffer, 64);
        Brytec::UsbPacket packet;
        packet.length = rxBuffer[1];
        if (packet.length <= 62) {
            memcpy(packet.data, &rxBuffer[2], packet.length);
            send(packet);
        }
    }
}