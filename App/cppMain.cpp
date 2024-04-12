#include "cppMain.h"

#include "CanBus.h"
#include "EBrytecApp.h"
#include "MsTimeout.h"
#include "Usb.h"
#include "gpio.h"
#include "stm32g4xx_hal.h"
#include "usart.h"
#include "usbd_cdc_if.h"

MsTimeout brytecTimeout(10);

void cppMain()
{
    Brytec::EBrytecApp::initalize();

    if (Brytec::EBrytecApp::isDeserializeOk())
        printf("DeserializeOk\n");
    else
        printf("Deserialize FAIL!\n");

    while (1) {

        Usb::update();

        Brytec::EBrytecApp::processCanCommands();

        if (brytecTimeout.isTimeout())
            Brytec::EBrytecApp::update(brytecTimeout.getTimestepMs());
    }
}