#include "Usb.h"

#include "BinaryBufferSerializer.h"
#include "usbd_cdc_if.h"

void Usb::send(Brytec::CanExtFrame& frame)
{
    Brytec::BinaryBufferSerializer ser(m_buffer, 64);
    ser.writeRaw<uint32_t>(frame.id);
    ser.writeRaw<uint8_t>(frame.dlc);
    ser.writeRaw<uint8_t>(frame.data[0]);
    ser.writeRaw<uint8_t>(frame.data[1]);
    ser.writeRaw<uint8_t>(frame.data[2]);
    ser.writeRaw<uint8_t>(frame.data[3]);
    ser.writeRaw<uint8_t>(frame.data[4]);
    ser.writeRaw<uint8_t>(frame.data[5]);
    ser.writeRaw<uint8_t>(frame.data[6]);
    ser.writeRaw<uint8_t>(frame.data[7]);

    CDC_Transmit_FS(m_buffer, ser.getWroteLenth());
}