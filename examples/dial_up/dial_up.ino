#include <SoftwareSerial.h>
#include <SimKafi.h>

SoftwareSerial SIM900Serial(14, 12);

void setup() {
  Serial.begin(9600);
  SIM900Serial.begin(9600);
  SIMKAFI SimKafi(SIM900Serial);

  SimKafi.dialUp("+XXxxxxxxxxxx");
  delay(20000);
  
  SimKafi.hangUp();
  delay(3000);

  SimKafi.redialUp();
  delay(10000);
  SimKafi.hangUp();
}

void loop() { }