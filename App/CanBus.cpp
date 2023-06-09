#include "CanBus.h"

#include "fdcan.h"
#include "stm32g4xx_hal_fdcan.h"

void CanBus::start()
{
    HAL_FDCAN_Start(&hfdcan1);
}

void CanBus::send(Brytec::CanExtFrame& frame)
{
    FDCAN_TxHeaderTypeDef header = {};
    header.Identifier = frame.id;
    header.IdType = FDCAN_EXTENDED_ID;
    header.TxFrameType = FDCAN_FRAME_CLASSIC;
    header.DataLength = FDCAN_DLC_BYTES_8;
    header.ErrorStateIndicator = FDCAN_ESI_PASSIVE;
    header.BitRateSwitch = FDCAN_BRS_OFF;
    header.FDFormat = FDCAN_FRAME_CLASSIC;
    header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    header.MessageMarker = 0;

    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &header, frame.data);
}