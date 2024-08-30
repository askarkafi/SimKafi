#include <SoftwareSerial.h>
#include <SimKafi.h>

SoftwareSerial SIM900Serial(7, 8);

void printRTC(SIMKAFIRTC rtc);

void setup() {
  Serial.begin(9600);
  SIM900Serial.begin(9600);
  SIMKAFI SimKafi(SIM900Serial);

  SIMKAFIRTC rtc;
  rtc.year = 2;
  rtc.month = 8;
  rtc.day = 8;
  rtc.hour = 8;
  rtc.minute = 0;
  rtc.second = 0;
  rtc.gmt = 8;

  Serial.print(F("Updating RTC to: "));
  printRTC(rtc);
  SimKafi.updateRtc(rtc);

  Serial.println(F("\n-------------------------------"));
  Serial.print("Current time: ");

  SIMKAFIRTC current = SimKafi.rtc();
  printRTC(current);
}

void loop() { }

void printRTC(SIMKAFIRTC rtc) {
  Serial.print(rtc.year);
  Serial.print(F("/"));
  Serial.print(rtc.month);
  Serial.print(F("/"));
  Serial.print(rtc.day);
  Serial.print(F(" "));
  Serial.print(rtc.hour);
  Serial.print(F(":"));
  Serial.print(rtc.minute);
  Serial.print(F(":"));
  Serial.print(rtc.second);
  Serial.print(F(" +"));
  Serial.print(rtc.gmt);
}