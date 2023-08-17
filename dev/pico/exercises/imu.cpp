                #include "rcc_stdlib.h"
                using namespace std;
                
                int main()
                {
                    stdio_init_all();
                    sleep_ms(1500);
                    cyw43_arch_init();  
                    cyw43_arch_gpio_put(0,1); 
                
                    rcc_init_i2c();

                    MPU6050 imu; 
                    imu.begin(i2c1); 
                    imu.calibrate(); 
                
                    while(true)
                    {
                        imu.update_pico(); 
                        float angvel_z = imu.getAngVelZ(); 
                        cout <<" z rotation: " << angvel_z << "\n";
                        sleep_ms(100);
                    }
                }
            