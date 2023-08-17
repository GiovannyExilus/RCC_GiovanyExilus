#include "rcc_stdlib.h"
using namespace std;

int main ()
{
    stdio_init_all();
    sleep_ms(1500);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0,1);

     rcc_init_pushbutton();
     while(true)
    { 
        if(!gpio_get(RCC_PUSHBUTTON))
        { 
            cout <<"PUSHBUTTON PRESSED!" <<'\n'; 
        }
    }

    
} // namespace stde


