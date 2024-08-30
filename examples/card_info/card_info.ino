#include <SoftwareSerial.h>
#include <SimKafi.h>

SoftwareSerial SIM900Serial(7, 8);

void setup() {
  Serial.begin(9600);
  SIM900Serial.begin(9600);
  SIMKAFI SimKafi(SIM900Serial);
  uint8_t phonebookIndex = 1;

  SIMKAFICardAccount accountInfo;
  accountInfo.name = "Nathanne Isip";
  accountInfo.number = "00000000000";
  accountInfo.numberType = SIMKAFI_PHONEBOOK_INTERNATIONAL;

  Serial.println(F("Storing a phonebook account..."));
  SimKafi.savePhonebook(phonebookIndex, accountInfo);
  Serial.println(F("Account stored!"));

  SIMKAFICardAccount retrieved = SimKafi.retrievePhonebook(phonebookIndex);
  Serial.println(F("Retrieving phonebook..."));
  Serial.println(F("-----------------------"));

  Serial.print(F("Name: "));
  Serial.println(retrieved.name);

  Serial.print(F("Number: "));
  Serial.println(retrieved.number);

  Serial.print(F("Number type: "));
  switch(retrieved.numberType) {
    case 129:
      Serial.println(F("International"));
      break;

    case 145:
      Serial.println(F("National"));
      break;

    default:
      Serial.println(F("Unknown"));
      break;
  }
}

void loop() { }