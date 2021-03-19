#include "GPS.h"

std::string last_loc = NULL_COORDINATE;

void GPSinit(){
	Serial2.begin(9600,SERIAL_8N1,RX2,TX2);
//  Serial.println("GPS Set-up Ready, Collecting Location Updates...");
}

std::string gprmcParser(const String& data){
	if(data.substring(1,6) == "GPRMC"){
		// Finding Index of Coordinates
		int cIndex = 0;
		byte indexCount = 0;
		while(indexCount++ < 3){
			cIndex = data.indexOf(",",cIndex+1);
		}
		// Getting the coordinates
		String lat = data.substring(cIndex+1,data.indexOf(",",cIndex+1));
		cIndex = data.indexOf(",",cIndex+1);
	//    char latDir = data.charAt(cIndex+1);      //N or S
		String lon = data.substring(cIndex+3,data.indexOf(",",cIndex+3)); 
		cIndex = data.indexOf(",",cIndex+3);
	//    char lonDir = data.charAt(cIndex+1);      //E or W
	//    Serial.println("Lat: "+lat+latDir+" Long: "+lon+lonDir);
		// Converting coordinates into degrees
		String coord = "";
		double deg = lat.substring(0,2).toFloat();
		double minutes = lat.substring(2).toFloat();
		deg += minutes/60.000000;
		if(deg == 0.000000f){
		  return NULL_COORDINATE;
		}
		coord+=String(deg,4);//+latDir;
		coord+=",";
		deg = lon.substring(0,3).toFloat();
		minutes = lon.substring(3).toFloat();
		deg += minutes/60.000000;
		if(deg == 0.000000f){
		  return NULL_COORDINATE;
		}
		coord+=String(deg,4);//+lonDir;
		coord = "0"+String(coord.length(),HEX)+coord;
		return std::string(coord.c_str());
	}
	return NULL_COORDINATE;
}

std::string getGPS(){
	String gpsData;
	if(Serial2.available() > 0){
		while (Serial2.available() > 0) {
			gpsData+=((char)(Serial2.read()));
		}
	}
	std::string new_loc = gprmcParser(gpsData);
	last_loc = (new_loc != NULL_COORDINATE)?new_loc:last_loc;
	return last_loc;
}
