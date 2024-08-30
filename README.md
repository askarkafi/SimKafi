# Arduino SIM900/SIM800 Comprehensive Library (کتابخانه  آردوین SIM900)

![Arduino CI](https://github.com/Askarkafi/SimKafi/actions/workflows/arduino_ci.yml/badge.svg) ![Arduino Lint](https://github.com/Askarkafi/SimKafi/actions/workflows/arduino_lint.yml/badge.svg)
![Arduino Release](https://img.shields.io/badge/Library%20Manager-1.1.0-red?logo=Arduino)
[![License: LGPL3.0](https://img.shields.io/badge/License-LGPL3.0-yellow.svg)](https://github.com/Askarkafi/SimKafi/blob/main/LICENSE)

کتابخانه آردوینو SimKafi کارت یک کتابخانه آردوینو همه کاره و قدرتمند برای ارتباط با ماژول SIM900/SIM800 GSM/GPRS است. این کتابخانه طیف گسترده ای از عملکردها را برای کار با ماژول SIM900 ارائه می دهد، از جمله ارسال و دریافت تماس، ارسال و دریافت پیامک، به روز رسانی و استخراج داده های ساعت بلادرنگ، ارسال درخواست های HTTP و بازیابی اطلاعات مختلف در مورد وضعیت ماژول SIM900 و شبکه ای که به آن متصل است.

### ویژگی‌ها
مدیریت تماس‌ها: به‌راحتی تماس بگیرید و دریافت کنید.
ارتباط پیامکی: پیامک‌ها را به‌راحتی ارسال و دریافت کنید.
ساعت واقعی: داده‌های ساعت واقعی را از ماژول به‌روزرسانی و استخراج کنید.
درخواست‌های HTTP: درخواست‌های HTTP ارسال کرده و پاسخ‌ها را دریافت کنید.
استخراج اطلاعات: اطلاعات مربوط به اپراتور شبکه، وضعیت ماژول، اطلاعات سیم‌کارت و موارد دیگر را جمع‌آوری کنید.
مدیریت دفترچه تلفن: حساب‌های دفترچه تلفن را ذخیره و بازیابی کنید.
مستندسازی کامل: کد و نمونه‌های کاربردی به‌خوبی مستندسازی شده‌اند.
### شروع به کار
### نصب
برای استفاده از این کتابخانه، مراحل زیر را دنبال کنید:
برای استفاده از این کتابخانه، مراحل زیر را دنبال کنید:

1. کتابخانه را از  [repository](https://github.com/Askarkafi/SimKafi) مخزن GitHub دانلود کنید.
2. نرم‌افزار Arduino IDE خود را باز کنید.
3. روی Sketch -> Include Library -> Add .ZIP Library... کلیک کنید.
4. فایل ZIP کتابخانه دانلود شده را انتخاب کنید.
5. به‌صورت جایگزین، می‌توانید بر روی Library Manager کلیک کرده و "SIM900" را تایپ کنید تا این کتابخانه را برای پروژه‌های خود نصب کنید.


## استفاده
برای استفاده از ماژول SIM900 در کد آردوینو:

#include <SoftwareSerial.h>
#include <sim900.h>

SoftwareSerial shieldSerial(7, 8);  //RX و TX

void setup() {
  Serial.begin(9600);               // شروع ارتباط سریال
  shieldSerial.begin(9600);         // شروع ارتباط شیلد
  SIM900 sim900(shieldSerial);       // شروع شیلد SIM900

  // کد شما اینجا قرار می‌گیرد...
}

void loop() { }


## نمونه‌ها
مخزن شامل مجموعه‌ای از نمونه کدها است که ویژگی‌های کتابخانه را نشان می‌دهد. می‌توانید آنها را در پوشه [https://github.com/Askarkafi/SimKafi/examples](examples) پیدا کنید.

## مستندات

- [مستندات فارسی](https://askarkafi.github.io/SimKafi/fa)
- [Documentation in English](https://askarkafi.github.io/SimKafi/en)
