#ifndef CONFIG_H
#define CONFIG_H

#include <SimKafi.h>

extern SIMKAFI SimKafi;

// تنظیمات پین‌های سخت‌افزار
constexpr int SIMKAFI_RX_PIN = 14;
constexpr int SIMKAFI_TX_PIN = 12;
constexpr int LED_STATUS_PIN = D7;
constexpr int RESET_PIN = D8;

// تنظیمات سریال
constexpr long serial_baudrate = 115200;

// تنظیمات SMS
const char SMS_TARGET_NUMBER[] = "+989xxxxxxxxx";

// تعریف گزارش سریال و نمایشگر
#define USING_SERIAL_REPORT // فعال کردن گزارش سریال
// #define USING_LIQUID_CRYSTAL  // فعال کردن نمایشگر کاراکتری
// #define USING_KEY_INPUT       // فعال کردن ورودی میکروسوییچ

#endif
