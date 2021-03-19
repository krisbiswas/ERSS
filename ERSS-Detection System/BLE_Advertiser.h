#include "Arduino.h"
#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include "string"

#define SERVICE_UUID           "00001802-0000-1000-8000-00805F9B34FB"
#define TX_CHARACTERISTIC_UUID "00001802-0001-1000-8000-00805F9B34FB"
#define RX_CHARACTERISTIC_UUID "00001802-0002-1000-8000-00805F9B34FB"
//BASE UUID = XXXXXXXX-0000-1000-8000-00805F9B34FB
//Generic Access: 0x1800
//Immediate Alert: 0x1802
//Alert Notification Service: 0x1811

class ERSS{
  public:
    NimBLEService *pService;
    NimBLECharacteristic *txCharacteristic;
    NimBLECharacteristic *rxCharacteristic;
    NimBLEAdvertising *pAdvertising;

    ERSS();
    void startAdv(std::string msg);
    void stopAdv();
};

void startBroadcastAlert(std::string msg);

void stopBroadcastAlert();

std::string getResponse();
