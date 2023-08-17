#include "rcc_stdlib.h"
using namespace std;

int main()
{
    stdio_init_all();
    sleep_ms(1000);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0, 1);

    Servo s3; 
    ServoInit(&s3, 18, false, 50);
    ServoOn(&s3);
    
    while(true)
    {   
        ServoPosition(&s3, 50);
    }
}