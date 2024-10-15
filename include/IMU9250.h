#ifndef MPU9250_MS5637_H
#define MPU9250_MS5637_H

#include "Wire.h"
#include <Arduino.h>

// MPU9250 I2C address
#define MPU9250_ADDRESS 0x68
#define AK8963_ADDRESS  0x0C
#define MS5637_ADDRESS  0x76

// Magnetometer Registers
#define AK8963_WHO_AM_I  0x00
#define AK8963_CNTL      0x0A
#define AK8963_ASAX      0x10

// MPU9250 Registers
#define PWR_MGMT_1       0x6B
#define CONFIG           0x1A
#define GYRO_CONFIG      0x1B
#define ACCEL_CONFIG     0x1C
#define ACCEL_CONFIG2    0x1D
#define INT_PIN_CFG      0x37
#define INT_ENABLE       0x38
#define ACCEL_XOUT_H     0x3B
#define GYRO_XOUT_H      0x43
#define TEMP_OUT_H       0x41
#define WHO_AM_I_MPU9250 0x75

// MS5637 Commands
#define MS5637_RESET      0x1E
#define MS5637_CONVERT_D1 0x40
#define MS5637_CONVERT_D2 0x50
#define MS5637_ADC_READ   0x00

// Enums for sensor configurations
enum Ascale {
  AFS_2G = 0,
  AFS_4G,
  AFS_8G,
  AFS_16G
};

enum Gscale {
  GFS_250DPS = 0,
  GFS_500DPS,
  GFS_1000DPS,
  GFS_2000DPS
};

enum Mscale {
  MFS_14BITS = 0, // 0.6 mG per LSB
  MFS_16BITS      // 0.15 mG per LSB
};

// Function declarations
void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz);
void MahonyQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz);
void myinthandler();
void getMres();
void getGres();
void getAres();
void readMPU9250Data(int16_t * destination);
void readAccelData(int16_t * destination);
void readGyroData(int16_t * destination);
void readMagData(int16_t * destination);
int16_t readTempData();
void initAK8963(float * destination);
void initMPU9250();
void accelgyrocalMPU9250(float * dest1, float * dest2);
void magcalMPU9250(float * dest1, float * dest2);
void MPU9250SelfTest(float * destination);
void MS5637Reset();
unsigned char MS5637checkCRC(uint16_t * n_prom);
void I2Cscan();
void writeByte(uint8_t address, uint8_t subAddress, uint8_t data);
uint8_t readByte(uint8_t address, uint8_t subAddress);
void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest);
uint32_t MS5637Read(uint8_t CMD, uint8_t OSR);
void MS5637PromRead(uint16_t * destination);
void IMU9250_Setup();
void IMU9250_loop();

// Global variables
extern float aRes, gRes, mRes;
extern float magCalibration[3];
extern float gyroBias[3], accelBias[3], magBias[3], magScale[3];
extern float ax, ay, az, gx, gy, gz, mx, my, mz;
extern float pitch, yaw, roll;
extern float temperature;
extern float q[4];
extern int intPin;
extern bool newData;
extern uint16_t Pcal[8];
extern float beta;

#endif // MPU9250_MS5637_H