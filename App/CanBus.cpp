#include "CanBus.h"

#include "fdcan.h"
#include "stm32g4xx_hal_fdcan.h"
#include "EBrytecApp.h"
#include "Usb.h"

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo0ITs)
{
    Brytec::CanExtFrame frame;

    FDCAN_RxHeaderTypeDef header = {};
    /* Retrieve Rx messages from RX FIFO0 */
    HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &header, frame.data);
    frame.id = header.Identifier;

    // CanBus::send(frame);
    Brytec::EBrytecApp::brytecCanReceived(frame);
    Usb::send(frame);
}

void CanBus::start()
{
    HAL_FDCAN_Start(&hfdcan1);
    HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
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