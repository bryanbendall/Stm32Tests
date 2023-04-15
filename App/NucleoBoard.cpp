#include "BrytecBoard.h"

namespace Brytec {

void BrytecBoard::error(EBrytecErrors error)
{
    switch (error) {
    case EBrytecErrors::ModuleHeader:
        // std::cout << "Module header is wrong" << std::endl;
        break;
    case EBrytecErrors::NodeGroupHeader:
        // std::cout << "Node Group header is wrong" << std::endl;
        break;
    case EBrytecErrors::ModuleNotEnabled:
        // std::cout << "This module is not enabled" << std::endl;
        break;
    case EBrytecErrors::AddNodeFailed:
        // std::cout << "Failed to add node" << std::endl;
        break;
    case EBrytecErrors::NodeVectorOutOfSpace:
        // std::cout << "Node Vector out of space" << std::endl;
        break;
    case EBrytecErrors::FailedToCreateNode:
        // std::cout << "Failed to create node" << std::endl;
        break;
    case EBrytecErrors::NodeIndexOutOfBounds:
        // std::cout << "Node index out of bounds" << std::endl;
        break;
    case EBrytecErrors::BadAlloc:
        // std::cout << "Node group allocation failed" << std::endl;
        break;
    case EBrytecErrors::CanBufferFull:
        // std::cout << "Can Buffer Full" << std::endl;
        break;

    default:
        // std::cout << "Unknown Error" << std::endl;
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