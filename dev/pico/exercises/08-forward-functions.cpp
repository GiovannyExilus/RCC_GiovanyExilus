#include "rcc_stdlib.h"
using namespace std;

void move_forward(Motor* motorPointer, Left_Odom* left, Right_Odom* right, int count) {
    int initial_left = left->getCount();
    int initial_right = right->getCount();

    int current_left, current_right;

    while ((current_left < initial_left + count) && (current_right < initial_right + count)) {
        MotorPower(motorPointer, 50, 50);
        current_left = left->getCount();
        current_right = right->getCount();
    }
}

int main()
{
    stdio_init_all();
    sleep_ms(1500);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0,1);

    rcc_init_pushbutton();

    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000);
    MotorsOn(&motors);
    printf("AFTER MOTORS");

    Left_Odom left;
    Right_Odom right;
    printf("AFTER ODOM");

    int left_count = 0;
    int right_count = 0;
    int rot360deg = 260; 
    int rot90deg = 65; 


    while(true)
    {
        left_count = left.getCount();
        right_count = right.getCount();

        if(!gpio_get(RCC_PUSHBUTTON))
        {
            move_forward(&motors, &left, &right, 100); 
            MotorPower(&motors, 0, 0); 
        }
    }

}