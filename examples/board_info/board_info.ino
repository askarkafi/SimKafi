#include <SoftwareSerial.h>
#include <SimKafi.h>

SoftwareSerial SIM900Serial(14, 12);

void setup() {
  Serial.begin(115200);
  SIM900Serial.begin(9600);
  SIMKAFI SimKafi(SIM900Serial);

  Serial.println(F("Dumping board informations..."));
  Serial.println(F("-----------------------------------------"));

  Serial.print(F("Manufacturer:\t"));
  Serial.println(SimKafi.manufacturer());
  
  Serial.print(F("Firmware:\t"));
  Serial.println(SimKafi.softwareRelease());

  Serial.print(F("Chip Model:\t"));
  Serial.println(SimKafi.chipModel());

  Serial.print(F("Chip Name:\t"));
  Serial.println(SimKafi.chipName());

  Serial.print(F("IMEI:\t\t"));
  Serial.println(SimKafi.imei());
}

void loop() { }