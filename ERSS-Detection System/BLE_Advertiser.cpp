#include "BLE_Advertiser.h"

ERSS::ERSS(){
  NimBLEDevice::init("ERSS");
  NimBLEServer *pServer = NimBLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);  
  txCharacteristic = pService->createCharacteristic(TX_CHARACTERISTIC_UUID,NIMBLE_PROPERTY::READ);
  rxCharacteristic = pService->createCharacteristic(RX_CHARACTERISTIC_UUID,NIMBLE_PROPERTY::READ|NIMBLE_PROPERTY::WRITE);
  pService->start();
  pAdvertising = NimBLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->addTxPower();
//  Serial.println("BLE Device Set-up Ready...");
}

void ERSS::startAdv(std::string msg){
  txCharacteristic->setValue(msg);
  pAdvertising->start();
}
void ERSS::stopAdv(){
  NimBLEDevice::deinit(true);
}


ERSS* erss = NULL;

void startBroadcastAlert(std::string msg){
  if(erss == NULL){
    Serial.println("ERSS BLE Created");
    erss = new ERSS();
  }
  erss->startAdv(msg);
}

void stopBroadcastAlert(){
  erss->stopAdv();
  erss = NULL;
//  Serial.println("ERSS BLE Destroyed");
}

std::string getResponse(){
//  Serial.printf("Transmitting/: %s\n",erss->txCharacteristic->getValue().c_str());
  return erss->rxCharacteristic->getValue();
}
