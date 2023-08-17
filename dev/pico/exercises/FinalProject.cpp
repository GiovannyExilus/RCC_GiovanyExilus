#include "rcc_stdlib.h"
using namespace std;

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
    rcc_init_lidar_single(&lidar);

    // rcc_init_lidar(&lidar);

    Servo s3;
    ServoInit(&s3, 18, false, 50);
    ServoOn(&s3); 

    int left_count = 0;
    int right_count = 0;
    int rot360deg = 260; 
    int rot90deg = 31; 
    uint16_t dist;

    bool searching = false;
    bool go_forward = false;
    bool go_right = false;
    bool go_left = false;

    left_count = left.getCount();
    right_count = right.getCount();

    while(true)
    {
        //dist = getFastReading(&lidar);
        cout << "Distance: " << dist << '\n';

        if(!gpio_get(RCC_PUSHBUTTON))
        {
            go_forward = true;
        }

        if(go_forward)
        {
            // dist = getFastReading(&lidar);
            ServoPosition(&s3, 50);
            dist = lidar.readRangeSingleMillimeters();
            MotorPower(&motors, 60, 60);
            sleep_ms(85);
            if (dist <300)
            {
                MotorPower(&motors, -10, -10);
             go_forward = false;
                searching = true;
                ServoPosition(&s3, 0);
                sleep_ms(80);
            }
        } 
        if (searching) 
        {
            for(int i = 0; i < 100; i++)
            {
                ServoPosition(&s3, i);
                sleep_ms(20);
                dist = lidar.readRangeSingleMillimeters();
                if (dist > 300)
                {
                    if(i>50)
                    {
                        searching = false;
                        go_left = true;
                        right.setZero();
                        left.setZero();
                        break;
                    }
                    else if (i < 50)
                    {
                        searching = false;
                        go_right = true;
                        right.setZero();
                        left.setZero();
                        break;
                    }
                }
            }
        }
        if (go_left) 
        {
            cout << "Go left\n";
            MotorPower(&motors, 0, 60);
            //get count right motor
            right_count = right.getCount();
            if (right_count >= rot90deg)
            {
                go_left = false;
                go_forward = true;
            }
            if(left_count >= 100 && right_count >= 100)
            {
                MotorPower(&motors, 0, 60); 
            }
            
        } 
        if (go_right) 
        {
            cout << "Go right\n";
            MotorPower(&motors, 60, 0);
            //get count left motor
            left_count = left.getCount();
            if (left_count >= rot90deg)
            {
                go_right = false;
                go_forward = true;
            }
            if(left_count >= 175 && right_count >= 175)
            {
                MotorPower(&motors, 60, 0); 
            }
        }

            
    }
}


