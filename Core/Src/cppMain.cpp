#include "cppMain.h"

#include "CanBus.h"
#include "EBrytecApp.h"
#include "Usb.h"
#include "gpio.h"
#include "stm32g4xx_hal.h"
#include "usart.h"
#include "usbd_cdc_if.h"

static uint64_t lastMillis = 0;
uint8_t data = 0;

void cppMain()
{
    Brytec::EBrytecApp::initalize();

    // if (Brytec::EBrytecApp::isDeserializeOk())
    //     printf("Des succ");
    // else
    //     printf("Des fail");

    CanBus::start();

    while (1) {
        // uint8_t data[] = "Hello\n";
        // HAL_UART_Transmit(&hlpuart1, data, 6, 100);

        // static uint32_t tick = 0;

        // if (HAL_GetTick() != tick && HAL_GetTick() % 100 == 0) {
        //     tick = HAL_GetTick();
        //     // HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

        // data++;
        // Brytec::CanExtFrame frame;
        // frame.id = 99;
        // frame.data[0] = 23;
        // frame.data[1] = 34;
        // frame.data[2] = 45;
        // frame.data[3] = 56;
        // frame.data[4] = 67;
        // frame.data[5] = 78;
        // frame.data[6] = 89;
        // frame.data[7] = data;

        // CanBus::send(frame);

        //     usb.send(frame);

        //     // HAL_Delay(10);

        //     frame.id = 23;
        //     usb.send(frame);
        // }

        Usb::update();

        // HAL_Delay(1);

        // Brytec //////////////////////////////
        uint64_t difference = HAL_GetTick() - lastMillis;
        if (difference > 1) {
            float timestep = ((float)difference * 0.001f);
            lastMillis = HAL_GetTick();

            Brytec::EBrytecApp::update(timestep);
        }
        /////////////////////////////////////////
    }
}