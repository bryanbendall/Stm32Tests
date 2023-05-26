#include "BrytecBoard.h"

#include "Deserializer/BinaryArrayDeserializer.h"
#include "NucleoBoardDefs.h"
#include "Usb.h"
#include "gpio.h"
#include <stdio.h>
#include <string.h>

#define PROGMEM
#include "Program.h"

namespace Brytec {

Brytec::BinaryArrayDeserializer deserializer(nullptr, 0);
uint8_t* s_configData = (uint8_t*)progmem_data;
uint32_t s_dataSize = sizeof(progmem_data);

BinaryDeserializer* BrytecBoard::getDeserializer()
{
    BinaryArrayDeserializer des(s_configData, s_dataSize);
    deserializer = des;
    return &deserializer;
}

void BrytecBoard::error(EBrytecErrors error)
{
    switch (error) {
    case EBrytecErrors::ModuleHeader:
        printf("Module header is wrong");
        break;
    case EBrytecErrors::NodeGroupHeader:
        printf("Node Group header is wrong");
        break;
    case EBrytecErrors::ModuleNotEnabled:
        printf("This module is not enabled");
        break;
    case EBrytecErrors::AddNodeFailed:
        printf("Failed to add node");
        break;
    case EBrytecErrors::NodeVectorOutOfSpace:
        printf("Node Vector out of space");
        break;
    case EBrytecErrors::FailedToCreateNode:
        printf("Failed to create node");
        break;
    case EBrytecErrors::NodeIndexOutOfBounds:
        printf("Node index out of bounds");
        break;
    case EBrytecErrors::BadAlloc:
        printf("Node group allocation failed");
        break;
    case EBrytecErrors::CanBufferFull:
        printf("Can Buffer Full");
        break;

    default:
        printf("Unknown Error");
        break;
    }
}

void BrytecBoard::setupBrytecCan(uint32_t mask, uint32_t filter)
{
}

void BrytecBoard::setupPin(uint16_t index, IOTypes::Types type)
{
}

void BrytecBoard::shutdownAllPins()
{
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
}

float BrytecBoard::getPinValue(uint16_t index)
{
    return 0.0f;
}

float BrytecBoard::getPinVoltage(uint16_t index)
{
    return 0.0f;
}

float BrytecBoard::getPinCurrent(uint16_t index)
{
    return 0.0f;
}

void BrytecBoard::setPinValue(uint16_t index, IOTypes::Types type, float value)
{
    bool state = value > 0.001f;

    switch (index) {
    case BT_PIN_Onboard_LED:
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, (GPIO_PinState)state);
        break;

    default:
        break;
    }
}

static Usb* s_usb = nullptr;
void BrytecBoard::setUsb(Usb* usb)
{
    s_usb = usb;
}

void BrytecBoard::sendBrytecCan(CanExtFrame frame)
{
    if (s_usb)
        s_usb->send(frame);
}

void BrytecBoard::ReserveConfigSize(uint16_t size)
{
    static bool progmem = true;
    if (!progmem) {
        free(s_configData);
    }
    progmem = false;
    // add extra 8 in case there is not a full packet
    s_dataSize = size;
    s_configData = (uint8_t*)malloc(size + 8);
}

void BrytecBoard::updateConfig(uint8_t* data, uint32_t size, uint32_t offset)
{
    memcpy(s_configData + offset, data, size);
}
}