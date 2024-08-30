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

/**
 * 
 * @file SIMKAFI_Defs.h
 * @author [Nathanne Isip](https://github.com/nthnn)
 * @brief This header defines various data structures and enumerations for the SIMKAFI GSM/GPRS module interaction.
 * 
 */

#ifndef SIMKAFI_DEFS_H
#define SIMKAFI_DEFS_H

/**
 * 
 * @enum SIMKAFIDialResult
 * @brief An enumeration representing the possible results of a dialing operation with the SIMKAFI module.
 *
 * This enumeration encapsulates different dialing results, providing detailed information about the outcome of
 * a call initiation process.
 * 
 */
typedef enum _SIMKAFIDialResult {
    /// No dial tone detected, indicating a failed call initiation.
    SIMKAFI_DIAL_RESULT_NO_DIALTONE,

    /// The line is busy, preventing a call from being established.
    SIMKAFI_DIAL_RESULT_BUSY,

    /// No carrier signal detected, resulting in a call failure.
    SIMKAFI_DIAL_RESULT_NO_CARRIER,

    /// No answer from the remote party, signifying an unsuccessful call attempt.
    SIMKAFI_DIAL_RESULT_NO_ANSWER,

    /// An error occurred during the dialing process, causing the call to fail.
    SIMKAFI_DIAL_RESULT_ERROR,

    /// The dialing operation was successful, and a call has been established.
    SIMKAFI_DIAL_RESULT_OK
} SIMKAFIDialResult;

/**
 * 
 * @enum SIMKAFIOperatorFormat
 * @brief An enumeration representing the available operator format options for the SIMKAFI module.
 *
 * This enumeration defines different ways to manage operator selection, allowing users to control how the SIMKAFI
 * module interacts with mobile network operators.
 * 
 */
typedef enum _SIMKAFIOperatorFormat {
    /// Automatically select the mobile network operator, simplifying the process.
    SIMKAFI_OPERATOR_FORMAT_AUTO,

    /// Manually specify and select the desired mobile network operator.
    SIMKAFI_OPERATOR_FORMAT_MANUAL,

    /// Deregister from the current network, suspending network registration.
    SIMKAFI_OPERATOR_FORMAT_DEREGISTER,

    /// Set operator without network registration, useful in specific scenarios.
    SIMKAFI_OPERATOR_FORMAT_SET_ONLY,

    /// Combine manual and automatic operator selection for flexibility.
    SIMKAFI_OPERATOR_FORMAT_MANUAL_AUTO
} SIMKAFIOperatorFormat;

/**
 * @param i Integer input to be casted.
 * @return A valid SIMKAFIOperatorFormat value.
 * 
 * @brief A function to safely cast from integer value to SIMKAFIOperatorFormat. Invalid inputs are casted to default value of SIMKAFI_OPERATOR_FORMAT_AUTO.
 * 
 * From C++11 up to newer versions of C++, enumerators are considered as a specific type rather than integer 
 * values. The same is true for newer Arduino compilers, too. So impilicit cast of integer value to an enum type is no longer allowed. For the sake of the safety of an explicit
 * cast is better to first check the range of the input. 
*/
inline SIMKAFIOperatorFormat intToSIMKAFIOperatorFormat(uint8_t i){
    if(i < SIMKAFIOperatorFormat::SIMKAFI_OPERATOR_FORMAT_AUTO ||
        i > SIMKAFIOperatorFormat::SIMKAFI_OPERATOR_FORMAT_MANUAL_AUTO)
        return SIMKAFIOperatorFormat::SIMKAFI_OPERATOR_FORMAT_AUTO;

    return static_cast<SIMKAFIOperatorFormat>(i);
}

/**
 * 
 * @enum SIMKAFIOperatorMode
 * @brief An enumeration representing different operating modes for the SIMKAFI module.
 *
 * This enumeration provides options for configuring the operational mode of the SIMKAFI module, allowing
 * users to adapt the module's behavior based on network and connectivity requirements.
 * 
 */
typedef enum _SIMKAFIOperatorMode {
    /// Standard GSM (2G) operating mode.
    SIMKAFI_OPERATOR_MODE_GSM,

    /// Compact GSM operating mode, optimized for resource-constrained environments.
    SIMKAFI_OPERATOR_MODE_GSM_COMPACT,

    /// UTRAN (3G) operating mode, suitable for 3G network connectivity.
    SIMKAFI_OPERATOR_MODE_UTRAN,

    /// GSM with EGPRS (2.5G) operating mode, offering enhanced data rates.
    SIMKAFI_OPERATOR_MODE_GSM_EGPRS,

    /// UTRAN HSDPA operating mode, enabling high-speed data access.
    SIMKAFI_OPERATOR_MODE_UTRAN_HSDPA,

    /// UTRAN HSUPA operating mode, focused on high-speed uplink data transmission.
    SIMKAFI_OPERATOR_MODE_UTRAN_HSUPA,

    /// UTRAN HSDPA and HSUPA combined mode for versatile 3G connectivity.
    SIMKAFI_OPERATOR_MODE_UTRAN_HSDPA_HSUPA,

    /// E-UTRAN (4G) operating mode, for advanced 4G LTE network connectivity.
    SIMKAFI_OPERATOR_MODE_E_UTRAN
} SIMKAFIOperatorMode;

/**
 * @param i Integer input to be casted.
 * @return A valid SIMKAFIOperatorMode value.
 * 
 * @brief A function to safely cast from integer value to SIMKAFIOperatorMode. Invalid inputs are casted to default value of SIMKAFI_OPERATOR_MODE_GSM.
 * 
 * From C++11 up to newer versions of C++, enumerators are considered as a specific type rather than integer 
 * values. The same is true for newer Arduino compilers, too. So impilicit cast of integer value to an enum type is no longer allowed. For the sake of the safety of an explicit
 * cast is better to first check the range of the input. 
*/
inline SIMKAFIOperatorMode intToSIMKAFIOperatorMode(int i){
    if(i < SIMKAFIOperatorMode::SIMKAFI_OPERATOR_MODE_GSM ||
        i > SIMKAFIOperatorMode::SIMKAFI_OPERATOR_MODE_E_UTRAN)
        return SIMKAFIOperatorMode::SIMKAFI_OPERATOR_MODE_GSM;

    return static_cast<SIMKAFIOperatorMode>(i);
}

/**
 * 
 * @enum SIMKAFICardService
 * @brief An enumeration representing the available card service types for the SIMKAFI module.
 *
 * This enumeration defines various card services, allowing users to configure the module for specific communication needs.
 * 
 */
typedef enum _SIMKAFICardService {
    /// Asynchronous card service for data communication.
    SIMKAFI_CARD_SERVICE_ASYNC,

    /// Synchronous card service for coordinated data exchange.
    SIMKAFI_CARD_SERVICE_SYNC,

    /// PAD (Packet Assembler/Disassembler) access service.
    SIMKAFI_CARD_SERVICE_PAD_ACCESS,

    /// Packet service for data transmission.
    SIMKAFI_CARD_SERVICE_PACKET,

    /// Voice service for voice calls.
    SIMKAFI_CARD_SERVICE_VOICE,

    /// Fax service for facsimile communication.
    SIMKAFI_CARD_SERVICE_FAX
} SIMKAFICardService;

/**
 * @param i Integer input to be casted.
 * @return A valid SIMKAFICardService value.
 * 
 * @brief A function to safely cast from integer value to SIMKAFICardService. Invalid inputs are casted to default value of SIMKAFI_CARD_SERVICE_ASYNC.
 * 
 * From C++11 up to newer versions of C++, enumerators are considered as a specific type rather than integer 
 * values. The same is true for newer Arduino compilers, too. So impilicit cast of integer value to an enum type is no longer allowed. For the sake of the safety of an explicit
 * cast is better to first check the range of the input. 
*/
inline SIMKAFICardService intToSIMKAFICardService(uint8_t i){
    if(i < SIMKAFICardService::SIMKAFI_CARD_SERVICE_ASYNC ||
        i > SIMKAFICardService::SIMKAFI_CARD_SERVICE_FAX)
        return SIMKAFICardService::SIMKAFI_CARD_SERVICE_ASYNC;

    return static_cast<SIMKAFICardService>(i);
}

/**
 * 
 * @enum SIMKAFIPhonebookType
 * @brief An enumeration representing the phonebook types for storing contacts in the SIMKAFI module.
 *
 * This enumeration defines different phonebook types, allowing users to manage and organize contact information
 * based on their needs, such as national and international phonebooks.
 * 
 */
typedef enum _SIMKAFIPhonebookType {
    /// National phonebook for storing local contacts.
    SIMKAFI_PHONEBOOK_NATIONAL       = 145,

    /// International phonebook for storing global contacts.
    SIMKAFI_PHONEBOOK_INTERNATIONAL  = 129,

    /// An unspecified or unknown phonebook type.
    SIMKAFI_PHONEBOOK_UNKNOWN        = 0
} SIMKAFIPhonebookType;

/**
 * 
 * @struct SIMKAFIOperator
 * @brief A structure representing mobile network operator information.
 *
 * This structure holds information about the mobile network operator's operating mode, format, and name.
 * 
 */
typedef struct _SIMKAFIOperator {
    /// The operating mode of the mobile network operator.
    SIMKAFIOperatorMode mode;

    /// The operator selection format.
    SIMKAFIOperatorFormat format;

    /// The name of the mobile network operator.
    String name;
} SIMKAFIOperator;

/**
 * 
 * @struct SIMKAFIRTC
 * @brief A structure representing real-time clock (RTC) information.
 *
 * This structure stores date and time information, including day, month, year, hour, minute, second, and GMT offset.
 * 
 */
typedef struct _SIMKAFIRTC {
    /// Date component: day.
    uint8_t day;
    
    /// Date component: month.
    uint8_t month;
    
    /// Date component: year.
    uint8_t year;

    /// Time component: hour.
    uint8_t hour;
    
    /// Time component: minute.
    uint8_t minute;
    
    /// Time component: second.
    uint8_t second;

    /// GMT (Greenwich Mean Time) offset in hours.
    int8_t gmt;
} SIMKAFIRTC;

/**
 * 
 * @struct SIMKAFIAPN
 * @brief A structure representing Access Point Name (APN) configuration for mobile data.
 *
 * This structure holds information about the APN, username, and password required for mobile data connectivity.
 * 
 */
typedef struct _SIMKAFIAPN {
    /// The Access Point Name (APN) for data connectivity.
    String apn;

    /// The username for APN authentication.
    String username;

    /// The password for APN authentication.
    String password;
} SIMKAFIAPN;

/**
 * 
 * @struct SIMKAFIHTTPHeader
 * @brief A structure representing an HTTP header key-value pair.
 *
 * This structure stores an HTTP header field as a key-value pair, facilitating the construction of HTTP requests.
 * 
 */
typedef struct _SIMKAFIHTTPHeader {
    /// The header field key.
    String key;

    /// The header field value.
    String value;
} SIMKAFIHTTPHeader;

/**
 * 
 * @struct SIMKAFIHTTPRequest
 * @brief A structure representing an HTTP request.
 *
 * This structure holds information about an HTTP request, including the HTTP method, data, domain, resource, status,
 * port, and an array of HTTP headers.
 * 
 */
typedef struct _SIMKAFIHTTPRequest {
    /// The HTTP method for the request (e.g., GET, POST).
    String method;

    /// The data to be included in the request (e.g., POST data).
    String data;

    /// The domain or server to which the request is sent.
    String domain;

    /// The resource or URL path to access on the server.
    String resource;

    /// The status of the HTTP request.
    uint8_t status;

    /// The port on which the server is listening (e.g., 80 for HTTP).
    uint16_t port;

    /// An array of HTTP headers associated with the request.
    SIMKAFIHTTPHeader *headers;

    /// The number of HTTP headers in the array.
    uint16_t header_count;
} SIMKAFIHTTPRequest;

/**
 * 
 * @struct SIMKAFIHTTPResponse
 * @brief A structure representing an HTTP response.
 *
 * This structure contains information about an HTTP response, including the HTTP status code, an array of HTTP headers,
 * and the response data.
 * 
 */
typedef struct _SIMKAFIHTTPResponse {
    /// The HTTP status code of the response.
    uint16_t status;

    /// An array of HTTP headers included in the response.
    SIMKAFIHTTPHeader *headers;

    /// The number of HTTP headers in the array.
    uint16_t header_count;

    /// The data received in the HTTP response, such as HTML content or JSON data.
    String data;
} SIMKAFIHTTPResponse;

/**
 * 
 * @struct SIMKAFICardAccount
 * @brief A structure representing a card account, including name, number, type, and service information.
 *
 * This structure stores information related to a card account, making it useful for managing and accessing
 * card-based services and communication.
 * 
 */
typedef struct _SIMKAFICardAccount {
    /// The name associated with the card account.
    String name;
    
    /// The card's phone number.
    String number;

    /// The card's type (e.g., SIM card).
    uint8_t type;
    
    /// The card's speed or data rate.
    uint8_t speed;

    /// The type of phonebook (national, international) where the number is stored.
    SIMKAFIPhonebookType numberType;

    /// The type of card service (e.g., voice, data) associated with the card account.
    SIMKAFICardService service;
} SIMKAFICardAccount;

/**
 * 
 * @struct SIMKAFIPhonebookCapacity
 * @brief A structure representing the capacity of a phonebook memory type.
 *
 * This structure provides information about the capacity of a specific phonebook memory type, including the type of
 * memory, the number of entries used, and the maximum number of entries that can be stored.
 * 
 */
typedef struct _SIMKAFIPhonebookCapacity {
    /// The type of phonebook memory (e.g., "SM" for SIM memory).
    String memoryType;

    /// The number of entries used in the phonebook memory.
    uint8_t used;

    /// The maximum number of entries that can be stored in the phonebook memory.
    uint8_t max;
} SIMKAFIPhonebookCapacity;

/**
 * 
 * @struct SIMKAFISignal
 * @brief A structure representing signal strength and bit error rate information.
 *
 * This structure stores information about the signal strength (RSSI) and bit error rate (BER) of the SIMKAFI module's
 * network connection, which is crucial for assessing the quality of the cellular signal.
 * 
 */
typedef struct _SIMKAFISignal {
    /// Received Signal Strength Indication (RSSI) in decibels (dBm).
    uint8_t rssi;

    /// Bit Error Rate (BER) as a unitless ratio.
    uint8_t bit_error_rate;
} SIMKAFISignal;

#endif