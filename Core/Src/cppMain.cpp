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

        Usb::update();

        Brytec::EBrytecApp::processCanCommands();

        // Brytec //////////////////////////////
        uint64_t difference = HAL_GetTick() - lastMillis;
        if (difference > 10) {
            float timestep = ((float)difference * 0.001f);
            lastMillis = HAL_GetTick();

            Brytec::EBrytecApp::update(timestep);
        }
        /////////////////////////////////////////
    }
}