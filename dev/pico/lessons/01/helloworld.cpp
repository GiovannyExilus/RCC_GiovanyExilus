#include "rcc_stdlib.h"
using namespace std;

int divide (int a, int b) {
   int result = a/b;
   return result;
}

void classifyGrades(int grade) {
    if ((grade <= 100) && (grade>=90)) {
        printf("student got an A"/n);
        cout
    }
    if ((grade<=89)  && (grade>=80)) {
        printf("Student got a B");
        cout
    }
    if ((grade <=79) && (grade>=70)) {
        printf("Student got a C");
        cout
}

int main(void)
{
    stdio_init_all();

    if(cyw43_arch_init())
    {
        cout << "CYW43 init failed!" << "\n";
    }

    cyw43_arch_gpio_put(0, 1);

    int x = 7;
    int y = 2;

    int result = divide(x, y);

    while (true) {
 	    printf("%d\n", result);   
     	sleep_ms(100);
    }

}
