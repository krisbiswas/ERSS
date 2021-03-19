#include "Arduino.h"
#include "string.h"
#define NULL_COORDINATE "NULL"
#define RX2 16
#define TX2 17

void GPSinit();

std::string gprmcParser(const String& data);

std::string getGPS();
