#include <SoftwareSerial.h>
#include <SimKafi.h>

SoftwareSerial SIM900Serial(14, 12);

void setup() {
    Serial.begin(115200);

    SIM900Serial.begin(9600);
    SIMKAFI SimKafi(SIM900Serial);
    Serial.println(
        SimKafi.sendSMS("+98xxxxxxxxxx", "Hello, world!!")
         ? "Sent!"
         : "Not sent.");
}

void loop() {}