/*
 * This file is part of the SIMKAFI Arduino Shield library.
 * Copyright (c) 2023 Nathanne Isip
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "simKafi.h"

void SIMKAFI::sendCommand(String message) {
    this->simKafi.println(message);
}
String SIMKAFI::getResponseForSMS(long timeout) {
    String response = "";
    long startTime = millis();
    
    while (millis() - startTime < timeout) {
        while (this->simKafi.available() > 0) {
            char c = this->simKafi.read();
            response += c;
            startTime = millis();  // Reset timeout on receiving new data
        }
    }

    response.trim();
    return response;
}
String SIMKAFI::getResponse() {
    delay(500);
    
    if(this->simKafi.available() > 0) {
        String response = this->simKafi.readString();
        response.trim();

        return response;
    }

    return "";
}

String SIMKAFI::getReturnedMode() {
    String response = this->getResponse();
    return response.substring(response.lastIndexOf('\n') + 1);
}

bool SIMKAFI::isSuccessCommand() {
    return this->getReturnedMode() == F("OK");
}

String SIMKAFI::rawQueryOnLine(uint16_t line) {
    String response = this->getResponse();
    String result = "";

    uint16_t currentLine = 0;
    for(int i = 0; i < response.length(); i++)
        if(currentLine == line && response[i] != '\n')
            result += response[i];
        else if(response[i] == '\n') {
            currentLine++;

            if(currentLine > line)
                break;
        }

    return result;
}

String SIMKAFI::queryResult() {
    String response = this->getResponse();
    String result = F("");

    int idx = response.indexOf(": ");
    if(idx != -1)
        result = response.substring(
            idx + 2,
            response.indexOf('\n', idx)
        );

    return result;
}

SIMKAFI::SIMKAFI(Stream& _simKafi):simKafi(_simKafi){}

bool SIMKAFI::handshake() {
    this->sendCommand(F("AT"));
    return this->isSuccessCommand();
}

bool SIMKAFI::isCardReady() {
    this->sendCommand(F("AT+CPIN?"));
    return this->isSuccessCommand();
}

bool SIMKAFI::changeCardPin(uint8_t pin) {
    if(pin > 9999)
        return false;

    this->sendCommand("AT+CPIN=\"" + String(pin) + "\"");
    return this->isSuccessCommand();
}

SIMKAFISignal SIMKAFI::signal() {
    SIMKAFISignal signal;
    signal.rssi = signal.bit_error_rate = 0;
    this->sendCommand("AT+CSQ");

    String response = this->queryResult();
    uint8_t delim = response.indexOf(',');

    if(delim == -1)
        return signal;

    signal.rssi = (uint8_t) response.substring(0, delim).toInt();
    signal.bit_error_rate = (uint8_t) response.substring(delim + 1).toInt();

    return signal;
}

// void SIMKAFI::close() {
//     this->simKafi->end();
// }

SIMKAFIDialResult SIMKAFI::dialUp(String number) {
    this->sendCommand("ATD+ " + number + ";");

    SIMKAFIDialResult result = SIMKAFI_DIAL_RESULT_ERROR;
    String mode = this->getReturnedMode();

    if(mode == F("NO DIALTONE"))
        result = SIMKAFI_DIAL_RESULT_NO_DIALTONE;
    else if(mode == F("BUSY"))
        result = SIMKAFI_DIAL_RESULT_BUSY;
    else if(mode == F("NO CARRIER"))
        result = SIMKAFI_DIAL_RESULT_NO_CARRIER;
    else if(mode == F("NO ANSWER"))
        result = SIMKAFI_DIAL_RESULT_NO_ANSWER;
    else if(mode == F("OK"))
        result = SIMKAFI_DIAL_RESULT_OK;

    return result;
}

SIMKAFIDialResult SIMKAFI::redialUp() {
    this->sendCommand(F("ATDL"));

    SIMKAFIDialResult result = SIMKAFI_DIAL_RESULT_ERROR;
    String mode = this->getReturnedMode();

    if(mode == F("NO DIALTONE"))
        result = SIMKAFI_DIAL_RESULT_NO_DIALTONE;
    else if(mode == F("BUSY"))
        result = SIMKAFI_DIAL_RESULT_BUSY;
    else if(mode == F("NO CARRIER"))
        result = SIMKAFI_DIAL_RESULT_NO_CARRIER;
    else if(mode == F("NO ANSWER"))
        result = SIMKAFI_DIAL_RESULT_NO_ANSWER;
    else if(mode == F("OK"))
        result = SIMKAFI_DIAL_RESULT_OK;

    return result;
}

SIMKAFIDialResult SIMKAFI::acceptIncomingCall() {
    this->sendCommand(F("ATA"));

    SIMKAFIDialResult result = SIMKAFI_DIAL_RESULT_ERROR;
    String mode = this->getReturnedMode();

    if(mode == F("NO CARRIER"))
        result = SIMKAFI_DIAL_RESULT_NO_CARRIER;
    else if(mode == F("OK"))
        result = SIMKAFI_DIAL_RESULT_OK;

    return result;
}

bool SIMKAFI::hangUp() {
    this->sendCommand(F("ATH"));
    return this->isSuccessCommand();
}

bool SIMKAFI::sendSMS(String number, String message) {
	
    this->handshake();

    this->sendCommand(F("AT+CMGF=1"));
    delay(500);
    this->sendCommand("AT+CMGS=\"" + number + "\"");
    delay(500);
    this->sendCommand(message);
    delay(500);
    this->simKafi.write(0x1a);

    return this->getReturnedMode().startsWith(">");
}

SIMKAFIOperator SIMKAFI::networkOperator() {
    SIMKAFIOperator simOperator;
    simOperator.mode = static_cast<SIMKAFIOperatorMode>(0);
    simOperator.format = static_cast<SIMKAFIOperatorFormat>(0);
    simOperator.name = "";

    this->sendCommand(F("AT+COPS?"));

    String response = this->queryResult();
    uint8_t delim1 = response.indexOf(','),
        delim2 = response.indexOf(',', delim1 + 1);

    simOperator.mode = intToSIMKAFIOperatorMode((uint8_t) response.substring(0, delim1).toInt());
    simOperator.format = intToSIMKAFIOperatorFormat((uint8_t) response.substring(delim1 + 1, delim2).toInt());
    simOperator.name = response.substring(delim2 + 2, response.length() - 2);

    return simOperator;
}

bool SIMKAFI::connectAPN(SIMKAFIAPN apn) {
    this->sendCommand(F("AT+CMGF=1"));
    if(!this->isSuccessCommand())
        return false;

    this->sendCommand(F("AT+CGATT=1"));
    if(!this->isSuccessCommand())
        return false;
    
    this->sendCommand(
        "AT+CSTT=\"" + apn.apn +
        "\",\"" + apn.username +
        "\",\"" + apn.password + "\""
    );

    return (this->hasAPN = this->isSuccessCommand());
}

bool SIMKAFI::enableGPRS() {
    if(!this->hasAPN)
        return false;

    this->sendCommand(F("AT+CIICR"));
    delay(1000);

    return this->isSuccessCommand();
}

SIMKAFIHTTPResponse SIMKAFI::request(SIMKAFIHTTPRequest request) {
    SIMKAFIHTTPResponse response;
    response.status = -1;

    if(!this->hasAPN)
        return response;

    this->sendCommand(
        "AT+CIPSTART=\"TCP\",\"" + request.domain +
        "\"," + String(request.port)
    );
    
    String resp = this->getResponse();
    resp.trim();

    delay(1500);
    if(!resp.endsWith(F("CONNECT OK")))
        return response;

    String requestStr = request.method + " " +
        request.resource + " HTTP/1.0\r\nHost: " +
        request.domain + "\r\n";

    for(int i = 0; i < request.header_count; i++)
        requestStr += request.headers[i].key + ": " +
            request.headers[i].value + "\r\n";

    if(request.data != "" || request.data != NULL)
        requestStr += request.data + "\r\n";

    requestStr += F("\r\n");
    this->sendCommand(requestStr);

    // TODO
    return response;
}

bool SIMKAFI::updateRtc(SIMKAFIRTC config) {
    this->sendCommand(
        "AT+CCLK=\"" + String(config.year <= 9 ? "0" : "") + String(config.year) +
        "/" + String(config.month <= 9 ? "0" : "") + String(config.month) +
        "/" + String(config.day <= 9 ? "0" : "") + String(config.day) +
        "," + String(config.hour <= 9 ? "0" : "") + String(config.hour) +
        ":" + String(config.minute <= 9 ? "0" : "") + String(config.minute) +
        ":" + String(config.second <= 9 ? "0" : "") + String(config.second) +
        "+" + String(config.gmt <= 9 ? "0" : "") + String(config.gmt) + "\""
    );

    return this->isSuccessCommand();
}

SIMKAFIRTC SIMKAFI::rtc() {
    SIMKAFIRTC rtc;
    rtc.year = rtc.month = rtc.day =
        rtc.hour = rtc.minute = rtc.second = 
        rtc.gmt = 0;

    this->sendCommand(F("AT+CMGF=1"));
    if(!this->isSuccessCommand())
        return rtc;

    this->sendCommand(F("AT+CENG=3"));
    if(!this->isSuccessCommand())
        return rtc;
    this->sendCommand(F("AT+CCLK?"));
    
    String time = this->queryResult();
    time = time.substring(1, time.length() - 2);

    uint8_t delim1 = time.indexOf('/'),
        delim2 = time.indexOf('/', delim1 + 1),
        delim3 = time.indexOf(',', delim2),
        delim4 = time.indexOf(':', delim3),
        delim5 = time.indexOf(':', delim4 + 1),
        delim6 = time.indexOf('+', delim5);

    rtc.year =  (uint8_t) time.substring(0, delim1).toInt();
    rtc.month = (uint8_t) time.substring(delim1 + 1, delim2).toInt();
    rtc.day = (uint8_t) time.substring(delim2 + 1, delim3).toInt();
    rtc.hour = (uint8_t) time.substring(delim3 + 1, delim4).toInt();
    rtc.minute = (uint8_t) time.substring(delim4 + 1, delim5).toInt();
    rtc.second = (uint8_t) time.substring(delim5 + 1, delim6).toInt();
    rtc.gmt = (uint8_t) time.substring(delim6 + 1).toInt();

    return rtc; 
}

bool SIMKAFI::savePhonebook(uint8_t index, SIMKAFICardAccount account) {
    this->sendCommand(
        "AT+CPBW=" + String(index) +
        ",\"" + account.number +
        "\"," + account.numberType +
        ",\"" + account.name + "\""
    );
    return this->isSuccessCommand();
}

SIMKAFICardAccount SIMKAFI::retrievePhonebook(uint8_t index) {
    this->sendCommand("AT+CPBR=" + String(index));

    SIMKAFICardAccount accountInfo;
    accountInfo.numberType = static_cast<SIMKAFIPhonebookType>(0);

    String response = this->queryResult();
    response = response.substring(response.indexOf(',') + 1);

    uint8_t delim1 = response.indexOf(','),
        delim2 = response.indexOf(',', delim1 + 1);

    accountInfo.number = response.substring(1, delim1 - 1);
    
    uint8_t type = (uint8_t) response.substring(delim1 + 1, delim2).toInt();
    if(type == 129 || type == 145)
        accountInfo.numberType = static_cast<SIMKAFIPhonebookType>(type);
    else accountInfo.numberType = static_cast<SIMKAFIPhonebookType>(0);

    accountInfo.name = response.substring(delim2 + 2, response.length() - 2);
    return accountInfo;
}

bool SIMKAFI::deletePhonebook(uint8_t index) {
    this->sendCommand("AT+CPBW=" + String(index));
    return this->isSuccessCommand();
}

SIMKAFIPhonebookCapacity SIMKAFI::phonebookCapacity() {
    SIMKAFIPhonebookCapacity capacity;
    capacity.used = capacity.max = 0;
    capacity.memoryType = F("");

    this->sendCommand("AT+CPBS?");

    String response = this->queryResult();
    uint8_t delim1 = response.indexOf(','),
        delim2 = response.indexOf(',', delim1 + 1);

    capacity.memoryType = response.substring(1, delim1 - 1);
    capacity.used = (uint8_t) response.substring(delim1 + 1, delim2).toInt();
    capacity.max = (uint8_t) response.substring(delim2 + 1).toInt();

    return capacity;
}

SIMKAFICardAccount SIMKAFI::cardNumber() {
    this->sendCommand(F("AT+CNUM"));

    SIMKAFICardAccount account;
    account.name = F("");

    String response = this->queryResult();
    if(response == F(""))
        return account;

    uint8_t delim1 = response.indexOf(','),
        delim2 = response.indexOf(',', delim1 + 1),
        delim3 = response.indexOf(',', delim2 + 1),
        delim4 = response.indexOf(',', delim3 + 1);

    account.name = response.substring(1, delim1 - 1);
    account.number = response.substring(delim1 + 2, delim2 - 1);
    account.type = (uint8_t) response.substring(delim2 + 1, delim3).toInt();
    account.speed = (uint8_t) response.substring(delim3 + 1, delim4).toInt();
    account.service = intToSIMKAFICardService((uint8_t) response.substring(delim4 + 1).toInt());
    account.numberType = static_cast<SIMKAFIPhonebookType>(0);

    return account;
}

String SIMKAFI::manufacturer() {
    this->sendCommand(F("AT+GMI"));
    return this->rawQueryOnLine(2);
}

String SIMKAFI::softwareRelease() {
    this->sendCommand(F("AT+GMR"));

    String result = this->rawQueryOnLine(2);
    result = result.substring(result.lastIndexOf(F(":")) + 1);

    return result;
}

String SIMKAFI::imei() {
    this->sendCommand(F("AT+GSN"));
    return this->rawQueryOnLine(2);
}

String SIMKAFI::chipModel() {
    this->sendCommand(F("AT+GMM"));
    return this->rawQueryOnLine(2);
}

String SIMKAFI::chipName() {
    this->sendCommand(F("AT+GOI"));
    return this->rawQueryOnLine(2);
}

String SIMKAFI::ipAddress() {
    this->sendCommand(F("AT+CIFSR"));
    return this->rawQueryOnLine(2);
}

int SIMKAFI::getSMSCount() {
    this->sendCommand(F("AT+CPMS?"));
    String response = this->getResponse();
    
    if(response.indexOf("ERROR") != -1)
        return -1;

    // استخراج تعداد پیام‌ها از پاسخ
    int startIndex = response.indexOf(",") + 1;
    int endIndex = response.indexOf(",", startIndex);
    return response.substring(startIndex, endIndex).toInt();
}

bool SIMKAFI::readSMS(int index, String& sender, String& message) {
    this->sendCommand("AT+CMGR=" + String(index));
    String response = this->getResponseForSMS(5000);  // استفاده از getResponse سفارشی

    if(response.indexOf("ERROR") != -1)
        return false;

    int senderStartIndex = response.indexOf("\"",response.indexOf(",")) + 1;
    int senderEndIndex = response.indexOf("\"", senderStartIndex);
    sender = response.substring(senderStartIndex, senderEndIndex);

    int messageStartIndex = response.indexOf("\r\n", senderEndIndex) + 2;
    int messageEndIndex = response.lastIndexOf("\r\n");
    message = response.substring(messageStartIndex, messageEndIndex);

    return true;
}

bool SIMKAFI::deleteSMS(int index) {
    this->sendCommand("AT+CMGD=" + String(index));
    return this->isSuccessCommand();
}

bool SIMKAFI::saveDraft(String number, String message) {
    this->sendCommand(F("AT+CMGW=\"") + number + F("\""));
    delay(500);
    this->sendCommand(message);
    delay(500);
    this->simKafi.write(0x1a);  // ارسال Ctrl+Z برای ذخیره پیام
    
    return this->isSuccessCommand();
}

bool SIMKAFI::searchSMS(String searchTerm, String& result) {
    this->sendCommand(F("AT+CMGL=\"ALL\""));
    String response = this->getResponseForSMS(10000);

    int startIndex = response.indexOf(searchTerm);
    if(startIndex != -1) {
        result = response.substring(startIndex, response.indexOf("\r\n", startIndex));
        return true;
    }

    return false;
}


bool SIMKAFI::deleteAllReadSMS() {
    this->sendCommand(F("AT+CMGDA=\"DEL READ\""));
    return this->isSuccessCommand();
}

bool SIMKAFI::sendFlashSMS(String number, String message) {
    this->sendCommand(F("AT+CSMP=49,167,0,240"));  // تنظیم برای ارسال فلش پیامک
    return this->sendSMS(number, message);
	//this->sendCommand(F("AT+CSMP"));
	this->sendCommand(F("AT+CSMP=49,167,0,0"));
}

bool SIMKAFI::enableDeliveryReports() {
    this->sendCommand(F("AT+CSMP=49,167,0,1"));  // فعالسازی گزارش تحویل
    return this->isSuccessCommand();
}

int SIMKAFI::getUnreadSMSCount() {
    this->sendCommand(F("AT+CPMS?"));
    String response = this->getResponse();
    
    if(response.indexOf("ERROR") != -1)
        return -1;

    int startIndex = response.indexOf(",") + 1;
    int endIndex = response.indexOf(",", startIndex);
    return response.substring(startIndex, endIndex).toInt();
}

bool SIMKAFI::readUnreadSMS(int index, String& sender, String& message) {
    this->sendCommand("AT+CMGR=" + String(index) + ",1");
    return this->readSMS(index, sender, message);
}

bool SIMKAFI::sendCNMICommand(int mode, int mt, int bm, int ds, int bfr) {
    String command = "AT+CNMI=" + String(mode) + "," + String(mt) + "," + String(bm) + "," + String(ds) + "," + String(bfr);
    
	this->sendCommand(command);
    
    return this->isSuccessCommand();
}

void SIMKAFI::setSMSReceivedCallback(void (*callback)(String, String)) {
    onSMSReceived = callback;
}

void SIMKAFI::setCallReceivedCallback(void (*callback)()) {
    onCallReceived = callback;
}

void SIMKAFI::setSMSDeliveredCallback(void (*callback)()) {
    onSMSDelivered = callback;
}

int SIMKAFI::parseIndexFromResponse(String response) {
    int indexStart = response.indexOf(',') + 1;
    return response.substring(indexStart).toInt();
}

void SIMKAFI::handleSerialEvent() {
    if (simKafi.available()) {
        String response = getResponse();  // دریافت پاسخ از ماژول

        if (response.indexOf("+CMTI:") != -1) {
            int index = parseIndexFromResponse(response);
            String sender, message;
            if (readSMS(index, sender, message)) {
                 if (onSMSReceived != nullptr) {
					onSMSReceived(sender, message);
				}
            }
        } 
        else if (response.indexOf("RING") != -1) {
            if (onCallReceived != nullptr) {
                onCallReceived();
            }
        }
        else if (response.indexOf("+CSQ:") != -1) {
            // وضعیت شبکه یا سیگنال
            SIMKAFISignal sig = signal();
            // پردازش وضعیت سیگنال
        }
        else if (response.indexOf("+CDS:") != -1) {
            if (onSMSDelivered != nullptr) {
                onSMSDelivered();
            }
        }
        else if (response.indexOf("OK") != -1) {
            // پاسخ مثبت به AT Command
            // اقدامات لازم
        }
        else if (response.indexOf("ERROR") != -1) {
            // پاسخ خطا به AT Command
            // اقدامات لازم
        }
        else if (response.indexOf("+CGATT:") != -1) {
            // وضعیت GPRS
            // پردازش وضعیت GPRS
        }
        // دیگر رویدادهای احتمالی
    }
}
