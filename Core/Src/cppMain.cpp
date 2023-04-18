#include "cppMain.h"

#include "EBrytecApp.h"
#include "Usb.h"
#include "gpio.h"
#include "stm32g4xx_hal.h"
#include "usart.h"
#include "usbd_cdc_if.h"

static uint64_t lastMillis = 0;
Brytec::EBrytecApp app;
Usb usb;
uint8_t data = 0;

void cppMain()
{

    Brytec::BinaryDeserializer des;
    app.deserializeModule(des);

    // if (Brytec::EBrytecApp::isDeserializeOk())
    //     printf("Des succ");
    // else
    //     printf("Des fail");

    app.setupModule();
    app.setupPins();

    while (1) {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        // uint8_t data[] = "Hello\n";
        // HAL_UART_Transmit(&hlpuart1, data, 6, 100);

        // uint8_t usb[] = "From usb cdc";
        // CDC_Transmit_FS(usb, 12);

        data++;
        Brytec::CanExtFrame frame;
        frame.id = 99;
        frame.data[0] = data;
        frame.data[1] = data * 2;
        frame.data[2] = 45;
        frame.data[3] = 56;
        frame.data[4] = 67;
        frame.data[5] = 78;
        frame.data[6] = 89;
        frame.data[7] = 91;
        usb.send(frame);

        app.update(0.5f);

        HAL_Delay(500);

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