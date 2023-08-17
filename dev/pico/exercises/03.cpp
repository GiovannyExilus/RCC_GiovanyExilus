#include "rcc_stdlib.h"
using namespace std;

int main()
{
    stdio_init_all();    
    sleep_ms(1500);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0,1);

    rcc_init_pushbutton();

    int array[100]; 

    for (int i = 0; i < 100; ++i) { 
        array[i] = i*10; 
    }

    int i = 0; 

    while(true){
        sleep_ms(100);

        if(!gpio_get(RCC_PUSHBUTTON))
        {
            cout << "i = " << i << ", value = " << array[i] << '\n'; 
            i++; 
        }
    }
}

