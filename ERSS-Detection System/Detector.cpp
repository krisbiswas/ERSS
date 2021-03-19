#include "Detector.h"

//const uint8_t trigPin = 2;    // Trigger
//const uint8_t echoPin = 4;    // Echo
MPU6050 mpu;
int16_t ax, ay, az;
struct accVect last_acc;

void sensor_init(){
	Wire.begin();                      // Initialize comunication
	mpu.initialize();
//	setMPUOffset();
	mpu.setFullScaleAccelRange(RANGE);// 3 = +/-16g
	
//	pinMode(trigPin, OUTPUT);
//	pinMode(echoPin, INPUT);
//  Serial.println("Sensors Set-up Ready...");
}
/*
int distance(){
	digitalWrite(trigPin, LOW);
	delayMicroseconds(10);
	digitalWrite(trigPin, HIGH);
	duration = pulseIn(echoPin, HIGH);
  
//	Convert the time*speed to distance
	cm = (duration/2) * 0.0343;     // Divide by 29.1 or multiply by 0.0343
  
	Serial.print(cm);
	Serial.println("cm");
}
*/
bool accident_detector(struct accVect acc){
//  Serial.print(acc.ax-last_acc.ax);
//  Serial.print("\t");
//  Serial.print(acc.ay-last_acc.ay);
//  Serial.print("\t");
//  Serial.print(acc.az-last_acc.az);
  if(abs(acc.ax-last_acc.ax)>LIMIT || abs(acc.ay-last_acc.ay)>LIMIT || abs(acc.az-last_acc.az) > LIMIT){
    return true;
  }
  last_acc.ax = acc.ax;
  last_acc.ay = acc.ay;
  last_acc.az = acc.az;
	return false;
}

struct accVect getAcc(){
	mpu.getAcceleration(&ax, &ay, &az);
  struct accVect acc;
  acc.ax = ax/DIVIDER;
  acc.ay = ay/DIVIDER;
  acc.az = az/DIVIDER;
  return acc;
//	return sqrt((ax*ax)+(ay*ay)+(az*az)) / DIVIDER;
}

/*
void setMPUOffset(){
    Serial.println("Updating internal sensor offsets...");
    mpu.setXAccelOffset(-1578);
    mpu.setYAccelOffset(-427);
    mpu.setZAccelOffset(707);
    mpu.setXGyroOffset(55);
    mpu.setYGyroOffset(-2);
    mpu.setZGyroOffset(17);
    Serial.print(mpu.getXAccelOffset()); Serial.print("\t"); // -1578
    Serial.print(mpu.getYAccelOffset()); Serial.print("\t"); // -427
    Serial.print(mpu.getZAccelOffset()); Serial.print("\t"); // 707
    Serial.print(mpu.getXGyroOffset()); Serial.print("\t"); // 55
    Serial.print(mpu.getYGyroOffset()); Serial.print("\t"); // -2
    Serial.print(mpu.getZGyroOffset()); Serial.print("\t"); // 17
    Serial.print("\n");
}
*/
