#include <SoftwareSerial.h>
#include <SimKafi.h>

SoftwareSerial SIM900Serial(14, 12);

void setup() {
  Serial.begin(9600);
  SIM900Serial.begin(9600);
  SIMKAFI SimKafi(SIM900Serial);

  Serial.println(
    SimKafi.handshake() ? "Handshaked!" : "Something went wrong."
  );
}

void loop() { }