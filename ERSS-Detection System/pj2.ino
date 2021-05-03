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

  if(is_accident_detected()){
//  if(digitalRead(stop_button)){
    accident_status = true;
    digitalWrite(buzz,HIGH);
    for (int i =1;i<=100;i++){
      delay(100);
      Serial.print(".");
      if(digitalRead(stop_button)){
        digitalWrite(buzz,LOW);
        accident_status = false;
        i=41;// break;
      }
    }
    Serial.println("");
  }
  std::string loc = getGPS();
  if(accident_status){
    Serial.printf("Accident Detected at: %s\n",loc.c_str());
    startBroadcastAlert(loc);
    std::string response = getResponse();
//    Serial.printf("Received: %s\n",response.c_str());/
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
