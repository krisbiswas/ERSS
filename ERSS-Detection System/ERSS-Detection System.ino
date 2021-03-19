#include "Detector.h"
#include "GPS.h"
#include "BLE_Advertiser.h"
//#include "Plotter.h"

// For using Plotter remove all serial data transfers
//double x,y,z; // global variables
//Plotter p; // create plotter

const uint8_t stop_button = 13;
uint8_t buzz = 33;
bool accident_status = false;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  pinMode(buzz,OUTPUT);
  
//  p.Begin(); // start plotter
//  p.AddTimeGraph("Acceleration 200", 200, "ax", x, "ay", y, "az", z);
//  p.AddTimeGraph("Acceleration 500", 500, "ax", x, "ay", y, "az", z);
//  p.AddTimeGraph("Acceleration 1000", 1000, "ax", x, "ay", y, "az", z);

  sensor_init();
  GPSinit();
  Serial.println("ERSS All Devices Ready");
  delay(20);
}

void loop() {
  if(digitalRead(stop_button)){
    digitalWrite(buzz,LOW);
    accident_status = false;
    stopBroadcastAlert();
  }

  struct accVect accVect = getAcc();
  Serial.print("Acc: ");
  Serial.print(accVect.ax);
  Serial.print("\t");
  Serial.print(accVect.ay);
  Serial.print("\t");
  Serial.print(accVect.az);
  if(accident_detector(accVect)){
//  if(digitalRead(stop_button)){
    accident_status = true;
    digitalWrite(buzz,HIGH);
  }
  std::string loc = getGPS();
  Serial.printf("\nGPS Location: %s\n",loc.c_str());
  if(accident_status){
    startBroadcastAlert(loc);
    std::string response = getResponse();
    Serial.printf("Received: %s\n",response.c_str());
    if(response.compare("MSG Delivered") == 0){
      stopBroadcastAlert();
      accident_status = false;
      digitalWrite(buzz,LOW);
    }
  }

//  x = accVect.ax;
//  y = accVect.ay;
//  z = accVect.az;
//  p.Plot();
  delay(50);
}
