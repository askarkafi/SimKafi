#include "config.h"
#include "DisplayModule.h"
#include "SIM900Module.h"

DisplayModule display;
extern SIMKAFI SimKafi;

void setup()
{
    display.begin(); // تنظیم اولیه نمایشگر
    setupSim();      // تنظیم اولیه ماژول SIMKAFI


    bool smsSent = SimKafi.sendSMS(SMS_TARGET_NUMBER, "Hello, world!!");
    display.show(smsSent ? "Sent!" : "Not sent.");
}

void loop() {
    // دریافت تعداد SMS‌ها
    int smsCount = SimKafi.getSMSCount();
    if (smsCount > 0) {
        display.show(("SMS Count: " + String(smsCount)).c_str());

        // خواندن آخرین SMS
        String sender;
        String message;
        if (SimKafi.readSMS(smsCount, sender, message)) {
            display.show(("From: " + sender).c_str());
            display.show(("Message: " + message).c_str());

            // حذف آخرین SMS
            if (SimKafi.deleteSMS(smsCount)) {
                display.show("SMS Deleted.");
            } else {
                display.show("Failed to delete SMS.");
            }
        } else {
            display.show("Failed to read SMS.");
        }
    } else {
        display.show("Failed to get SMS count.");
    }

    // تأخیر برای جلوگیری از اجرای مکرر
    delay(10000); // تأخیر 10 ثانیه‌ای
}