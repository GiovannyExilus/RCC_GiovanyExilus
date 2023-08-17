#include "rcc_stdlib.h"
using namespace std;

int main (void) {
    stdio_init_all();
   
    if(cyw43_arch_init())
    {
      cout << "cyw43 init failed!"  << "\r";
    }

    cyw43_arch_gpio_put(0, 1);

    while (true) {
      cyw43_arch_gpio_put(0, !(cyw43_arch_gpio_get(0)));
      sleep_ms(100);
      cout << "Hello\n";
    }
}
