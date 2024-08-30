#include <SoftwareSerial.h>
#include <SimKafi.h>

SoftwareSerial SIM900Serial(14, 12);

void setup() {
  Serial.begin(9600);

  SIM900Serial.begin(9600);
  SIMKAFI SimKafi(SIM900Serial);
  SIMKAFIPhonebookCapacity capacity = SimKafi.phonebookCapacity();

  Serial.println(F("Phonebook Capacity"));
  Serial.println(F("-------------------"));

  Serial.print(F("Memory Type:\t"));
  Serial.println(capacity.memoryType);

  Serial.print(F("Used:\t\t"));
  Serial.println(capacity.used);

  Serial.print(F("Max:\t\t"));
  Serial.println(capacity.max);
}

void loop() { }