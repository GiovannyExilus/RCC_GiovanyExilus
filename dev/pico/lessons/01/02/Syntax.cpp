#include "rcc_stdlib.h"
using namespace std;

int main () {
    stdio_init_all();

    if(cyw43_arch_init())
    {
      cout << "cyw43 init failed!"  << "\r";
    }

    cyw43_arch_gpio_put(0, 1);

    int x_loc = 1;
    int y_loc = 20;
    
    while (true) {
        printf("%d\n", x_loc);
        sleep_ms(500);
        x_loc = x_loc*3;
    }
}




/* int substraction(int a, int b) {

} */