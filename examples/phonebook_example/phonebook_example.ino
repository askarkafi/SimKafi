#include <SoftwareSerial.h>
#include <SimKafi.h>

SoftwareSerial SIM900Serial(7, 8);

void setup() {
  Serial.begin(9600);
  SIM900Serial.begin(9600);
  SIMKAFI SimKafi(SIM900Serial);
  uint8_t index = 1;

  SIMKAFICardAccount account;
  account.name = "Nathanne Isip";
  account.number = "00000000000";
  account.numberType = SIMKAFI_PHONEBOOK_NATIONAL;

  Serial.println(F("Storing to phonebook..."));
  if(!SimKafi.savePhonebook(index, account)) {
    Serial.println(F("Error saving to phonebook."));
    return;
  }

  Serial.println(F("Stored!"));
  Serial.println(F("--------------------------"));
  Serial.println(F("Retrieving..."));

  SIMKAFICardAccount retrieved = SimKafi.retrievePhonebook(index);
  Serial.print(F("Name:\t"));
  Serial.println(retrieved.name);

  Serial.print(F("Number:\t"));
  Serial.println(retrieved.number);

  Serial.print(F("Type:\t"));
  switch(retrieved.numberType) {
    case SIMKAFI_PHONEBOOK_INTERNATIONAL:
      Serial.println("International");
      break;

    case SIMKAFI_PHONEBOOK_NATIONAL:
      Serial.println("National");
      break;

    default:
      Serial.println("Unknown");
      break;
  }
}

void loop() { }