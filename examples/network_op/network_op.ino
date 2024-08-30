#include <SoftwareSerial.h>
#include <SimKafi.h>

SoftwareSerial SIM900Serial(14, 12);

void setup() {
  Serial.begin(9600);

  SIM900Serial.begin(9600);
  SIMKAFI SimKafi(SIM900Serial);
  SIMKAFIOperator network = SimKafi.networkOperator();

  Serial.println(F("SIMKAFI Current Network Operator"));
  Serial.println(F("-------------------------------"));
  Serial.print(F("Name:\t"));
  Serial.println(network.name);
  Serial.print(F("Mode:\t"));
  Serial.println(network.mode);
  Serial.print(F("Format:\t"));
  Serial.println(network.format);
}

void loop() { }
