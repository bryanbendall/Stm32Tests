#include "CanBusDefs.h"

#include "NucleoBoardDefs.h"

namespace CanBusDefs {

FDCAN_HandleTypeDef* getCanBus(uint8_t index)
{
    switch (index) {
    case BT_CAN_Hi_Lo:
        return &hfdcan1;
    }

    return nullptr;
}

uint8_t getCanBusIndex(FDCAN_HandleTypeDef* bus)
{
    if (bus == &hfdcan1)
        return BT_CAN_Hi_Lo;

    return UINT8_MAX;
}

}