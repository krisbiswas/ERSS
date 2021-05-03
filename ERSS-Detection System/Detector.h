#include "Arduino.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#define RANGE 3
#define DIVIDER 2048.0
#define LIMIT 8 // 4,8

const byte ADDR = 0x68; // MPU6050 I2C address

struct accVect{
  double ax=0,ay=0,az=0;
};

struct gyroVect{
  double gx=0,gy=0,gz=0;
};

void sensor_init();
/*
void setMPUOffset();

int distance();
*/
void getMotion();

bool is_accident_detected();
