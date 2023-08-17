#include "rcc_stdlib.h"
using namespace std;

void blink_led(int time){
    cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0)); 
    sleep_ms(time);
}

int main()
{   
    stdio_init_all();
    sleep_ms(100);
    cyw43_arch_init(); 
    cyw43_arch_gpio_put(0, 1); 

    rcc_init_pushbutton(); 

    bool blinking = false;

    while(true)
    {
        if(!gpio_get(RCC_PUSHBUTTON)){
            blinking = true;
        }

        if (blinking){
            blink_led(300);
        }
    }
}