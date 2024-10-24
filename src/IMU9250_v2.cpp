#include <Arduino.h>
#include <math.h>
#include <MPU9250_RegisterMap.h>
#include <IMU9250_v2.h>
#include <SparkFunMPU9250-DMP.h> // Include SparkFun MPU-9250-DMP library
#include <Wire.h> // Depending on your Arduino version, you may need to include Wire.h

const int intPin = 27;
MPU9250_DMP imu; // Create an instance of the MPU9250_DMP class
bool dataReady = false;
int countP = 0;
//unsigned long pastTime = micros();

float pitch;

void sensorInterupt() {
    dataReady = true;
}

void IMU9250setup() {

    pinMode(intPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(intPin), sensorInterupt, RISING);

    if (imu.begin()) {
        Serial.println("FAILED MPU9250");
    }
    Serial.println("dmp");
    int error = imu.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_SEND_RAW_ACCEL, 190);
    Serial.println(error);

    // imu.setSensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS); // Enable all sensors
    // // Gyro options are +/- 250, 500, 1000, or 2000 dps
    // imu.setGyroFSR(2000);
    // // Accel options are +/- 2, 4, 8, or 16 g
    // imu.setAccelFSR(2);

    // imu.setLPF(30); // Set LPF corner frequency to 5Hz

    // // The sample rate of the accel/gyro can be set using
    // // setSampleRate. Acceptable values range from 4Hz to 1kHz
    //imu.setSampleRate(1000);
    
    imu.enableInterrupt(1);
    imu.setIntLevel(INT_ACTIVE_HIGH);
    imu.setIntLatched(INT_50US_PULSE);

    Serial.println("Setup Done"); 
}

bool IMU9250loop() { //make return bool
    if ( dataReady )
    {
        // Use dmpUpdateFifo to update the ax, gx, qx, etc. values
        if ( imu.dmpUpdateFifo() == INV_SUCCESS )
        {
            //Serial.println("dataReady");
            imu.computeEulerAngles();
            pitch = imu.pitch;
            if (countP % 200 == 0) {
                // Serial.print("w x y z: ");
                // Serial.print(imu.qw);
                // Serial.print(" ");
                // Serial.print(imu.qx);
                // Serial.print(" ");
                // Serial.print(imu.qy);
                // Serial.print(" ");
                // Serial.println(imu.qz);
                // Serial.print("gx gy gz: ");
                // Serial.print(imu.gx);
                // Serial.print(" ");
                // Serial.print(imu.gy);
                // Serial.print(" ");
                // Serial.println(imu.gz);
                // Serial.print("Pitch Yaw Roll: ");
                // Serial.print(imu.pitch);
                // Serial.print(" ");
                // Serial.print(imu.yaw);
                // Serial.print(" ");
                // Serial.println(imu.roll);
            }
            countP++;
            

            // if (micros() - pastTime > 1000000) {
            //     Serial.println(count);
            //     pastTime = micros();
            //     count = 0;
            // }
            // The following variables will have data from the top of the FIFO:
            // imu.ax, imu.ay, imu.az, -- Accelerometer
            // imu.gx, imu.gy, imu.gz -- calibrated gyroscope
            // and imu.qw, imu.qx, imu.qy, and imu.qz -- quaternions
        }
        dataReady = false;
        return true;
    }
    return false;
}