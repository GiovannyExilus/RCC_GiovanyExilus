#include "rcc_stdlib.h"
using namespace std;

//setup instance of config struct
PID_control_config_t config;

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

    rcc_init_i2c(); 
    VL53L0X lidar; 
    rcc_init_lidar(&lidar);

    Servo s3;
    ServoInit(&s3, 18, false, 50);
    ServoOn(&s3); 

    int left_count = 0;
    int right_count = 0;
    int rot360deg = 260; 
    int rot90deg = 65; 

    int starting_count = 0;
    int number_of_right_turns = 2;
    uint16_t dist;

    bool go_forward = false;
    bool go_right = false;
    bool go_left = false;
    bool stop = false;

    left_count = left.getCount();
    right_count = right.getCount();

    while(true)
    {
        if(!gpio_get(RCC_PUSHBUTTON))
        {
            go_forward = true;
        }

        if(go_forward == true)
        {
            dist = getFastReading(&lidar); // gets lidar distance 
            MotorPower(&motors, 50, 50); // spins both wheels forwards
            if (dist < 400) // checks distance from wall
            {
                MotorPower(&motors, 0, 0); // makes car stop
                go_forward = false;
                go_right = true;
                starting_count = right.getCount();
            }
        } 

        if(go_right == true)
        {
            // start at some count because we moved forward
            // lets say we start at 50
            // we also know it takes 30 ticks of the right wheel to turn right
            // if we do MotorPower(&motors, 0, 100);
            // how do we stop the motors once we've gone + 50 ticks from where
            // we started
            while (right.getCount()< (starting_count + 50)) {
                MotorPower(&motors, 0, 100);
            }
            go_right = false;
            stop = true;
        }

        if(stop == true) {
            MotorPower(&motors, 0, 0);
            stop = false;
            if(number_of_right_turns <= 0) {
                go_right = false;
            } 
            else 
            {
                go_right = true;
                starting_count = right.getCount();
                number_of_right_turns = number_of_right_turns - 1;
            }
        }

    }
}


