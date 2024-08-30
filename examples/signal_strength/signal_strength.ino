#include <SoftwareSerial.h>
#include <SimKafi.h>

SoftwareSerial SIM900Serial(14, 12);

void setup() {
  Serial.begin(9600);

  SIM900Serial.begin(9600);
  SIMKAFI SimKafi(SIM900Serial);
  SIMKAFISignal signal = SimKafi.signal();

  Serial.println(F("Signal Strength"));
  Serial.println(F("-------------------"));

  Serial.print(F("RSSI:\t\t"));
  Serial.println(signal.rssi);

  Serial.print(F("Bit Error Rate:\t"));
  Serial.println(signal.bit_error_rate);
}

void loop() { }