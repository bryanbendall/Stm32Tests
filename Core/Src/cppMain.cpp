#include "cppMain.h"

#include "gpio.h"
#include "usart.h"
#include "usbd_cdc_if.h"

class something{

public:
    something(int b)
        : i(b)
    {

    }

    int i;
};

void cppMain(){
    while (1) {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        uint8_t data[] = "Hello\n";
        HAL_UART_Transmit(&hlpuart1, data, 6, 100);

        CDC_Transmit_FS(data, 6);

        HAL_Delay(500);

        something(2);

        if constexpr (true){
            HAL_UART_Transmit(&hlpuart1, data, 6, 100);
        }
    }
}