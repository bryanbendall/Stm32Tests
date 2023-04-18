#include "BrytecBoard.h"

#include <stdio.h>

namespace Brytec {

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
}

void BrytecBoard::sendBrytecCan(CanExtFrame frame)
{
}

}