#include "rcc_stdlib.h"
using namespace std;

int main(void)
{
    stdio_init_all();
    sleep_ms(100);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0, true); 

    Motor motors; 
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000); 
    MotorsOn(&motors); 

    while(true)
    {   
        sleep_ms(100); 

        if(!gpio_get(RCC_PUSHBUTTON)){
            
            MotorPower(&motors, 70, 70); 
            
        }

    }
}