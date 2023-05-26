#pragma once

#include "EBrytecApp.h"
#include "EBrytecCan.h"
#include "Usb/UsbDefs.h"

class Usb {

public:
    Usb() = default;

    void send(Brytec::CanExtFrame& frame);
    void send(Brytec::UsbPacket& packet);
    void update();

    void setApp(Brytec::EBrytecApp* app) { m_app = app; }

private:
    Brytec::EBrytecApp* m_app = nullptr;
};