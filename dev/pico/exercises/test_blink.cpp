#include "rcc_stdlib.h"
using namespace std;

void blink_led() {
    // repeat blink led steps
    cyw43_arch_gpio_put(0, !cyw43_arch_gpio_get(0));
    sleep_ms(100);
    cout << "Goodbye" << '\n';
}

int main (void) {
    stdio_init_all();
   
    if(cyw43_arch_init())
    {
      cout << "cyw43 init failed!"  << "\r";
    }

    cyw43_arch_gpio_put(0, 1);
    while (true) {
        blink_led();
    }
}