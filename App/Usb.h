#pragma once

#include "EBrytecCan.h"
#include "Usb/UsbDefs.h"

class Usb {

public:
    Usb() = default;

    void send(Brytec::CanExtFrame& frame);
    void send(Brytec::UsbPacket& packet);
    void update();
};