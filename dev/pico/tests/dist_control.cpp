#include "rcc_stdlib.h"
using namespace std;

int main () {
    stdio_init_all();

    if(cyw43_arch_init())
    {
      cout << "cyw43 init failed!"  << "\r";
    }

    cyw43_arch_gpio_put(0, 1);

    // Initialization steps
    //Init potentiometer and pushbutton
    rcc_init_potentiometer();
    rcc_init_pushbutton();

    //Init servo
    Servo s3;
    ServoInit(&s3, 18, false, 50);
    ServoOn(&s3);
    printf("AFTER SERVO");


    //Init motors
    Motor motors;
    MotorInit(&motors, RCC_ENB, RCC_ENA, 1000);
    MotorsOn(&motors);
    printf("AFTER MOTORS");

    //INit i2c and mpu6050    
    rcc_init_i2c();
    MPU6050 imu;
    imu.begin(i2c1);
    imu.calibrate();
    float accelx, accely, angvelz;
    printf("AFTER IMU");

    // //Odom
    Left_Odom left;
    Right_Odom right;
    printf("AFTER ODOM");

    // Lidar
    VL53L0X lidar;
    rcc_init_lidar(&lidar);

    // Control system variables
    float desired = 200;    // Desired distance
    float actual;           // Actual distance from lidar
    uint16_t lidar_reading; // Lidar reading
    float error;            // Error input to controller
    float kp = 1;           // Proportional gain
    float power;            // Power to motors

    // Control Loop
    while (true) {
        // Get the distance from the lidar
        lidar_reading = getFastReading(&lidar);
        // Convert the lidar distance from uint to float
        actual = static_cast<float>(lidar_reading);
        // Calculate the error
        error = desired - actual;
        // Caculate the controller output (kp*error)
        power = kp*error;
        // Saturate the controller output (dont allow outside of range -100->100)
        power = max(min(power, 100.f), -100.f);
        // Convert power to an integer and flip sign
        int power_int = static_cast<int>(power * (-1));
        // Apply the controller output (power) to the motors
        MotorPower(&motors, power_int, power_int);
        /* Note, below is all one line */
        cout << "des: " 
        << desired << " act: "
        << actual << " err: " 
        << error << " power: " 
        << power_int << "\n";
    }
}