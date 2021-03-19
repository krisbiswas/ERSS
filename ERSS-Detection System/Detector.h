#include "Arduino.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#define RANGE 3
#define DIVIDER 2048.0
#define LIMIT 8

const byte ADDR = 0x68; // MPU6050 I2C address

struct accVect{
  double ax=0,ay=0,az=0;
};

void sensor_init();
/*
void setMPUOffset();

int distance();
*/
struct accVect getAcc();

bool accident_detector(struct accVect acc);
