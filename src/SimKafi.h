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

#ifndef SIMKAFI_H
#define SIMKAFI_H

#include <Arduino.h>

#include "simKafi_defs.h"

/**
 * 
 * @class SIMKAFI
 * @brief A class for interfacing with the SIMKAFI GSM/GPRS module using Arduino and SoftwareSerial.
 *
 * This class provides a wide range of functionalities for working with the SIMKAFI module, including sending and receiving calls,
 * sending and receiving SMS, updating and extracting real-time clock data, sending HTTP requests, and retrieving various information
 * about the SIMKAFI module's status and the network it is connected to.
 * 
 */
class SIMKAFI {
private:
    /// The SoftwareSerial object used for communication with the SIMKAFI module.
    Stream& simKafi;

	// اشارهگرهای تابع برای کالبکها
    void (*onSMSReceived)(String sender, String message) = nullptr;
    void (*onCallReceived)() = nullptr;
	void (*onSMSDelivered)() = nullptr;
	
    /// A flag indicating whether Access Point Name (APN) configuration is set.
    bool hasAPN = false;

    /// Send a command to the SIMKAFI module.
    void sendCommand(String message);

    /// Check if the last command was successful.
    bool isSuccessCommand();

    /// Get the response from the SIMKAFI module.
    String getResponse();

	///Get the response from the sim900 module in specific timeout (for read message)
	String getResponseForSMS(long timeout);
	
    /// Get the returned operational mode from the SIMKAFI module.
    String getReturnedMode();

    /// Perform a raw query operation on a specified line.
    String rawQueryOnLine(uint16_t line);

    /// Retrieve the result of a query operation.
    String queryResult();
	
	int parseIndexFromResponse(String response);

public:
    /**
     * 
     * @brief Constructor for the SIMKAFI class.
     *
     * @param _simKafi A pointer to the SoftwareSerial object for communication with the SIMKAFI module.
     * 
     */
    SIMKAFI(Stream& _simKafi);
	
	// متدها برای تنظیم کالبکها
    void setSMSReceivedCallback(void (*callback)(String, String));
    void setCallReceivedCallback(void (*callback)());
	void setSMSDeliveredCallback(void (*callback)());

    // متد برای پردازش رویدادها
    void handleSerialEvent();
	
	/**
	 * @brief Sends the AT+CNMI command to configure the SMS message indications.
	 * 
	 * This function allows you to configure how the module will notify the microcontroller
	 * when an SMS message is received. It uses the AT+CNMI command to set the notification mode,
	 * message type, broadcast messages, delivery reports, and buffer storage.
	 * 
	 * @param mode Specifies the mode of SMS message indication. 
	 *        - 0: Buffer unread messages and do not notify the terminal.
	 *        - 1: Notify the terminal of new messages by sending a notification.
	 *        - 2: Directly forward received messages to the terminal.
	 * @param mt Specifies the type of messages to be forwarded to the terminal.
	 *        - 0: No message indications are forwarded.
	 *        - 1: Class 1 messages are forwarded.
	 *        - 2: Class 2 messages are forwarded.
	 * @param bm Specifies the handling of cell broadcast messages.
	 *        - Typically set to 0 to disable.
	 * @param ds Specifies the delivery reports for SMS.
	 *        - 0: Delivery reports are disabled.
	 *        - 1: Delivery reports are enabled.
	 * @param bfr Specifies the storage of messages in the buffer.
	 *        - 0: Disable buffer storage.
	 *        - 1: Enable buffer storage.
	 * 
	 * @return Returns true if the command was successfully executed and acknowledged with "OK". 
	 *         Returns false if there was an error or no response was received within the timeout period.
	 */
	bool sendCNMICommand(int mode, int mt, int bm, int ds, int bfr);



    /**
     * 
     * @brief Initialize communication with the SIMKAFI module and perform a handshake.
     *
     * @return True if the handshake is successful, false otherwise.
     * 
     */
    bool handshake();

    /**
     * 
     * @brief Close the communication with the SIMKAFI module.
     * 
     */
    void close();

    /**
     * 
     * @brief Check if the SIM card is ready.
     *
     * @return True if the SIM card is ready, false otherwise.
     * 
     */
    bool isCardReady();

    /**
     * 
     * @brief Change the PIN code of the SIM card.
     *
     * @param pin The new PIN code to set.
     * @return True if the PIN code change is successful, false otherwise.
     * 
     */
    bool changeCardPin(uint8_t pin);

    /**
     * 
     * @brief Get the signal strength and bit error rate of the network connection.
     *
     * @return A SIMKAFISignal structure containing signal strength and bit error rate information.
     * 
     */
    SIMKAFISignal signal();

    /**
     * 
     * @brief Initiate an outgoing call to a phone number.
     *
     * @param number The phone number to call.
     * @return The result of the dialing operation, as a SIMKAFIDialResult.
     * 
     */
    SIMKAFIDialResult dialUp(String number);

    /**
     * 
     * @brief Redial the last outgoing call.
     *
     * This function redials the last outgoing call to the same phone number.
     *
     * @return The result of the redialing operation, as a SIMKAFIDialResult.
     * 
     */
    SIMKAFIDialResult redialUp();

    /**
     * 
     * @brief Accept an incoming call.
     *
     * This function accepts an incoming call from another phone number.
     *
     * @return True if the call acceptance is successful, false otherwise.
     * 
     */
    SIMKAFIDialResult acceptIncomingCall();

    /**
     * 
     * @brief Hang up an active call.
     *
     * This function terminates an ongoing call.
     *
     * @return True if the call is successfully terminated, false otherwise.
     * 
     */
    bool hangUp();

    /**
     * 
     * @brief Send an SMS (Short Message Service).
     *
     * This function sends an SMS message to a specified phone number.
     *
     * @param number The recipient's phone number.
     * @param message The SMS message content.
     * @return True if the SMS is successfully sent, false otherwise.
     * 
     */
    bool sendSMS(String number, String message);

    /**
     * 
     * @brief Connect to an Access Point Name (APN) for mobile data.
     *
     * This function establishes a connection to an APN, enabling mobile data connectivity.
     *
     * @param apn An instance of the SIMKAFIAPN structure containing APN, username, and password information.
     * @return True if the APN connection is successful, false otherwise.
     * 
     */
    bool connectAPN(SIMKAFIAPN apn);

    /**
     * 
     * @brief Enable the General Packet Radio Service (GPRS) for data communication.
     *
     * This function enables GPRS for data transmission over the mobile network.
     *
     * @return True if GPRS is successfully enabled, false otherwise.
     * 
     */
    bool enableGPRS();

    /**
     * 
     * @brief Send an HTTP request to a remote server.
     *
     * This function sends an HTTP request to a specified server with the provided request parameters.
     *
     * @param request An instance of the SIMKAFIHTTPRequest structure representing the HTTP request.
     * @return A SIMKAFIHTTPResponse structure containing the HTTP response from the server.
     * 
     */
    SIMKAFIHTTPResponse request(SIMKAFIHTTPRequest request);

    /**
     * 
     * @brief Get information about the current network operator.
     *
     * This function retrieves information about the mobile network operator, including its operating mode, format, and name.
     *
     * @return A SIMKAFIOperator structure containing network operator information.
     * 
     */
    SIMKAFIOperator networkOperator();

    /**
     * 
     * @brief Get the SIM card number.
     *
     * This function retrieves information about the SIM card, including the card's name, number, type, speed,
     * the type of phonebook where the number is stored, and the card service.
     *
     * @return A SIMKAFICardAccount structure containing SIM card information.
     * 
     */
    SIMKAFICardAccount cardNumber();

    /**
     * 
     * @brief Get the real-time clock (RTC) information.
     *
     * This function retrieves the current date and time from the SIMKAFI module, including day, month, year, hour,
     * minute, second, and the GMT offset.
     *
     * @return A SIMKAFIRTC structure containing RTC information.
     * 
     */
    SIMKAFIRTC rtc();

    /**
     * 
     * @brief Update the SIMKAFI module's real-time clock (RTC).
     *
     * This function allows you to configure the SIMKAFI module's RTC with a new date, time, and GMT offset.
     *
     * @param config An instance of the SIMKAFIRTC structure containing the new RTC configuration.
     * @return True if the RTC update is successful, false otherwise.
     * 
     */
    bool updateRtc(SIMKAFIRTC config);

    /**
     * 
     * @brief Save a contact in the SIM card's phonebook.
     *
     * This function saves a contact entry in the SIM card's phonebook at the specified index.
     *
     * @param index The index at which to save the contact entry.
     * @param account An instance of the SIMKAFICardAccount structure containing the contact's information.
     * @return True if the contact is successfully saved, false otherwise.
     * 
     */
    bool savePhonebook(uint8_t index, SIMKAFICardAccount account);

    /**
     * 
     * @brief Delete a contact from the SIM card's phonebook.
     *
     * This function deletes a contact entry from the SIM card's phonebook at the specified index.
     *
     * @param index The index of the contact entry to delete.
     * @return True if the contact is successfully deleted, false otherwise.
     * 
     */
    bool deletePhonebook(uint8_t index);

    /**
     * 
     * @brief Retrieve a contact from the SIM card's phonebook.
     *
     * This function retrieves a contact entry from the SIM card's phonebook at the specified index.
     *
     * @param index The index of the contact entry to retrieve.
     * @return A SIMKAFICardAccount structure containing the contact's information.
     * 
     */
    SIMKAFICardAccount retrievePhonebook(uint8_t index);

    /**
     * 
     * @brief Get information about the capacity of the SIM card's phonebook.
     *
     * This function provides information about the capacity of the SIM card's phonebook memory type,
     * including the memory type, used entries, and the maximum number of entries.
     *
     * @return A SIMKAFIPhonebookCapacity structure containing phonebook capacity information.
     * 
     */
    SIMKAFIPhonebookCapacity phonebookCapacity();

    /**
     * 
     * @brief Get the manufacturer name of the SIMKAFI module.
     *
     * @return The manufacturer name as a String.
     * 
     */
    String manufacturer();

    /**
     * 
     * @brief Get the software release version of the SIMKAFI module.
     *
     * @return The software release version as a String.
     * 
     */
    String softwareRelease();

    /**
     * 
     * @brief Get the International Mobile Equipment Identity (IMEI) number of the SIMKAFI module.
     *
     * @return The IMEI number as a String.
     * 
     */
    String imei();

    /**
     * 
     * @brief Get the chip model of the SIMKAFI module.
     *
     * @return The chip model as a String.
     * 
     */
    String chipModel();

    /**
     * 
     * @brief Get the chip name of the SIMKAFI module.
     *
     * @return The chip name as a String.
     * 
     */
    String chipName();

    /**
     * 
     * @brief Get the IP address assigned to the SIMKAFI module.
     *
     * @return The assigned IP address as a String.
     * 
     */
    String ipAddress();
	
	/**
	 * @brief Get the number of SMS messages stored in the SIM card's memory.
	 *
	 * @return The number of SMS messages stored, or -1 if the command fails.
	 */
	int getSMSCount();
	
	/**
	 * @brief Read a specific SMS from the SIM card's memory.
	 *
	 * @param index The index of the SMS to read (starting from 1).
	 * @param sender The phone number of the SMS sender (output).
	 * @param message The content of the SMS (output).
	 * @return True if the SMS is read successfully, false otherwise.
	 */
	bool readSMS(int index, String& sender, String& message);

	/**
	 * @brief Delete a specific SMS from the SIM card's memory.
	 *
	 * @param index The index of the SMS to delete (starting from 1).
	 * @return True if the SMS is deleted successfully, false otherwise.
	 */
	bool deleteSMS(int index);

	/**
	 * @brief Save a draft SMS to the SIM card's memory.
	 *
	 * @param number The recipient's phone number.
	 * @param message The content of the SMS to save as a draft.
	 * @return True if the draft is saved successfully, false otherwise.
	 */
	bool saveDraft(String number, String message);

	/**
	 * @brief Search for an SMS containing a specific term.
	 *
	 * @param searchTerm The term to search for in the SMS messages.
	 * @param result The content of the SMS message found.
	 * @return True if an SMS containing the search term is found, false otherwise.
	 */
	bool searchSMS(String searchTerm, String& result);

	/**
	 * @brief Delete all read SMS messages from the SIM card's memory.
	 *
	 * @return True if all read SMS messages are deleted successfully, false otherwise.
	 */
	bool deleteAllReadSMS();
	
	/**
	 * @brief Delete all SMS messages from the SIM card's memory.
	 *
	 * @return True if all read SMS messages are deleted successfully, false otherwise.
	 */
	bool deleteAllSMS();
	

	/**
	 * @brief Send a flash SMS to a specific phone number.
	 *
	 * @param number The recipient's phone number.
	 * @param message The content of the SMS message to send.
	 * @return True if the flash SMS is sent successfully, false otherwise.
	 */
	bool sendFlashSMS(String number, String message);

	/**
	 * @brief Enable the delivery reports for sent SMS messages.
	 *
	 * @return True if delivery reports are enabled successfully, false otherwise.
	 */
	bool enableDeliveryReports();

	/**
	 * @brief Retrieve the count of unread SMS messages stored in the SIM card.
	 *
	 * @return The number of unread SMS messages stored in the SIM card.
	 */
	int getUnreadSMSCount();

	/**
	 * @brief Read an unread SMS from the SIM card's memory.
	 *
	 * @param index The index of the unread SMS to read (starting from 1).
	 * @param sender The phone number of the sender.
	 * @param message The content of the SMS message.
	 * @return True if the unread SMS is read successfully, false otherwise.
	 */
	bool readUnreadSMS(int index, String& sender, String& message);


};


#endif