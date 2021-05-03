#include "Detector.h"

//const uint8_t trigPin = 2;    // Trigger
//const uint8_t echoPin = 4;    // Echo
MPU6050 mpu;
int16_t ax, ay, az;
struct accVect last_acc;
struct accVect acc;

int16_t gx, gy, gz;
struct gyroVect gyro;
long time_past = 0;
long time_present = 0;

double g_roll = 0, g_pitch=0;

void sensor_init(){
	Wire.begin();                      // Initialize comunication
	mpu.initialize();
//	setMPUOffset();
	mpu.setFullScaleAccelRange(RANGE);// 3 = +/-16g
	mpu.setFullScaleGyroRange(1);// 1 = +/-500 deg/s

//  Serial.println("Sensors Set-up Ready...");
}

bool is_accident_detected(){
  getMotion();
/*////////////////////////////////////////////////////////////////
  double acc_roll,acc_pitch;
  acc_pitch = 180 * atan2(acc.ax, sqrt(acc.ay*acc.ay + acc.az*acc.az))/PI;
  acc_roll = 180 * atan2(acc.ay, sqrt(acc.ax*acc.ax + acc.az*acc.az))/PI;

  double delta_roll,delta_pitch;
  delta_roll = (gyro.gx)*(time_present-time_past)/(2000);
  g_roll += (abs(delta_roll) > 1)?delta_roll:0;
  delta_pitch = (gyro.gy)*(time_present-time_past)/(2000);
  g_pitch += (abs(delta_pitch) > 1)?delta_pitch:0;
  
//  double roll, pitch;
//  pitch = 0.96*g_pitch + 0.04*acc_pitch;
//  roll = 0.96*g_roll + 0.04*acc_roll;
  Serial.print(delta_roll);
  Serial.print("\t");
  Serial.print(delta_pitch);
  Serial.print("\t");
  Serial.print(g_roll);
  Serial.print("\t");
  Serial.println(g_pitch);
//  if(abs(roll) > 40 || abs(pitch) > 40){
//    return true;
//  }
//////////////////////////////////////////////////////////*/
  Serial.println("Delta_ax: "+String(acc.ax-last_acc.ax,3)+"\tDelta_ay: "+String(acc.ay-last_acc.ay,3)+"\tDelta_az: "+String(acc.az-last_acc.az,3));
  if(abs(acc.ax-last_acc.ax)>LIMIT || abs(acc.ay-last_acc.ay)>LIMIT || abs(acc.az-last_acc.az) > LIMIT){
    return true;
  }
  last_acc.ax = acc.ax;
  last_acc.ay = acc.ay;
  last_acc.az = acc.az;
	return false;
}

void getMotion(){
  time_past = time_present;
	mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	time_present = millis();
  acc.ax = ax/DIVIDER;
  acc.ay = ay/DIVIDER;
  acc.az = az/DIVIDER;
  gyro.gx = gx/65.5;
  gyro.gy = gy/65.5;
  gyro.gz = gz/65.5;
  Serial.println("ax: "+String(acc.ax,3)+"\tay: "+String(acc.ay,3)+"\taz: "+String(acc.az,3)+
                "\tgx: "+String(gyro.gx,3)+"\tgy: "+String(gyro.gy,3)+"\tgz: "+String(gyro.gz,3));
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
