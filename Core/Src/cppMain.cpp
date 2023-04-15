#include "cppMain.h"

#include "EBrytecApp.h"
#include "gpio.h"
#include "usart.h"
#include "usbd_cdc_if.h"
#include "stm32g4xx_hal.h"

static uint64_t lastMillis = 0;
Brytec::EBrytecApp app;

void cppMain()
{

    Brytec::BinaryDeserializer des;
    app.deserializeModule(des);

    // if (EBrytecApp::isDeserializeOk())
    //     Serial::SendString("Des succ", 8, true);
    // else
    //     Serial::SendString("Des fail", 8, true);

    app.setupModule();
    app.setupPins();

    while (1) {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        uint8_t data[] = "Hello\n";
        // HAL_UART_Transmit(&hlpuart1, data, 6, 100);

        uint8_t usb[] = "From usb cdc";
        CDC_Transmit_FS(usb, 12);

        app.update(0.5f);

        HAL_Delay(500);

        if constexpr (false) {
            HAL_UART_Transmit(&hlpuart1, data, 6, 100);
        }

        // Brytec //////////////////////////////
        uint64_t difference = HAL_GetTick() - lastMillis;
        if (difference > 1) {
            float timestep = ((float)difference * 0.001f);
            lastMillis = HAL_GetTick();

            app.update(timestep);
        }
        /////////////////////////////////////////
    }
}