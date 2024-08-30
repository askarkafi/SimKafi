#include "SIM900Module.h"
#include <SoftwareSerial.h>
#include "config.h"

SoftwareSerial SIM900Serial(SIMKAFI_RX_PIN, SIMKAFI_TX_PIN);
SIMKAFI SimKafi(SIM900Serial);

void setupSim(void)
{
    SIM900Serial.begin(9600);
    // می‌توانید بررسی‌های اولیه را در اینجا انجام دهید.
}