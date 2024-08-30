#include "DisplayModule.h"
#include "config.h"

#ifdef USING_LIQUID_CRYSTAL
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#endif

void DisplayModule::begin()
{
#ifdef USING_LIQUID_CRYSTAL
    lcd.begin(16, 2);
#endif
#ifdef USING_SERIAL_REPORT
    Serial.begin(serial_baudrate);
#endif
}

void DisplayModule::show(const char *Message)
{
#ifdef USING_LIQUID_CRYSTAL
    lcd.clear();
    lcd.print(Message);
#endif
#ifdef USING_SERIAL_REPORT
    Serial.println(Message);
#endif
}

void DisplayModule::showSignal(int signal)
{
    char buffer[16];
    sprintf(buffer, "Signal: %d", signal);
    show(buffer);
}
