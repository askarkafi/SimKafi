#include <SoftwareSerial.h>
#include <SimKafi.h>

SoftwareSerial SIM900Serial(14, 12);
SIMKAFI SimKafi(SIM900Serial);

void setup() {
    Serial.begin(115200);

    SIM900Serial.begin(9600);

    // انتظار برای آماده شدن ماژول
    delay(2000);
    
    SimKafi.sendCNMICommand(2,1,0,0,0);//"AT+CNMI=2,1,0,0,0"
    SimKafi.enableDeliveryReports();
    // تنظیم کال‌بک‌ها
    SimKafi.setSMSReceivedCallback(onSMSReceived);
    SimKafi.setCallReceivedCallback(onCallReceived);
    SimKafi.setSMSDeliveredCallback(onSMSDelivered);

    Serial.println(
        SimKafi.sendSMS("+98xxxxxxxxxx", "Hello, world!!")
         ? "Sent!"
         : "Not sent.");
}

void loop() {
    if (SIM900Serial.available()) {
        SimKafi.handleSerialEvent();
    }
}

// تعریف کال‌بک برای دریافت پیامک
void onSMSReceived(String sender, String message) {
    Serial.println("SMS Received:");
    Serial.println("Sender: " + sender);
    Serial.println("Message: " + message);
}

// تعریف کال‌بک برای تماس ورودی
void onCallReceived() {
    Serial.println("Incoming Call Detected!");
}

void onSMSDelivered() {
    Serial.println("SMS Delivered!");
}