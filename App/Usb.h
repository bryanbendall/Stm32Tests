#pragma once

#include "EBrytecCan.h"

class Usb {

public:
    Usb() = default;

    void send(Brytec::CanExtFrame& frame);

private:
    uint8_t m_buffer[64];
};