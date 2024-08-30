#include <SoftwareSerial.h>
#include <SimKafi.h>

SoftwareSerial SIM900Serial(7, 8);

void setup() {
  Serial.begin(9600);
  SIM900Serial.begin(9600);
  SIMKAFI SimKafi(SIM900Serial);

  SIMKAFIAPN access;
  access.apn = F("");
  access.username = F("");
  access.password = F("");

  if(!SimKafi.connectAPN(access)) {
    Serial.println(F("Failed to connect to APN."));
    return;
  }
  Serial.println(F("Connected to APN!"));

  bool gprsEnabled = SimKafi.enableGPRS();
  Serial.println(gprsEnabled ?
    F("GPRS was successfully enabled.") :
    F("Cannot start GPRS."));

  if(!gprsEnabled)
    return;
  Serial.println("IP Address: " + SimKafi.ipAddress());
}

void loop() { }