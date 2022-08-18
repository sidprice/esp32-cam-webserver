//
// ESP32 Module Preference handling.
//
//
//  Processing for the API extension commands for ESP32 modules.
//
// Author Sid Price
//
// Copyright Kevin Levesque 2022
//


#include <Arduino.h>

#include <Preferences.h>
#include "parsebytes.h"
/*
 *  Include the Preferences name definition file
 */
#include "pref_config.h"

#include "prefs.h"


//
// The following is the preferenes object, used to store network and other
// settiings for the system.
//
// TODO Move SPIFFS storage of camaera settings to Preferences
//

Preferences preferences ;

//
// Common preferences namespace variable storage
//
// TODO check if these need to be global variables
//
char strSSID[64] = {0} ;
char strNetPassphrase[64] = {0} ;
char strIPAddress[64] = {0} ;
byte ipAddress[4] = {0} ;
char strNetMask[64] = {0} ;
byte netMask[4] = {0} ;
char strGateway[64] = {0} ;
byte netGateway[4] = {0} ;
char strModuleType[64] = {0} ;

//
// Update the passed preference with the passed data
//
// Note this function assumes the host device has already initialized
// the preferences during its startup. Otherwise the function will fail
//

void prefs_update_string(char * key, char * value)
{
    preferences.begin("Common", false) ; // Open preferences common section for read/write
    preferences.putString(key, value) ;
    preferences.end() ;     // CLose the preferences
}

//
// This function is called during the device set up, it attempts to read the
// Network SSID, if this fails it assumes the preferences need initialization
// and sets all values to their defaults.
//
// The preferences are then read into variables for use by the module
//

void prefs_get_preferences(void)
{
    //
    // Open up the preferences and check if they have been initialized
    //
    //  TODO Refactor all preference code to separate files or a library to permit reuse on other module types
    //
    if (preferences.begin("Common", false) == false) {
        Serial.println("Failed to start preferences") ;
    }
    //
    // Attempt to read the Network SSID
    //
    preferences.getString(PREF_COMMON_NETWORK_SSID,strSSID, sizeof(strSSID)) ;
    if ( strSSID[0] == 0x00 )
    {
        Serial.println("Preferences need init") ;
        //
        // Since the SSID was not found the preferences need to be initialize
        // to the default values. These may be edited if required in the
        // "pref_config.h" file.
        //
        // Initialize the "Common" values.
        //      SSID, Network_Address, Network_Mask, and the Module_Type
        //
        preferences.putString(PREF_COMMON_NETWORK_SSID, PREF_COMMON_DEFAULT_SSID) ;
        preferences.putString(PREF_COMMON_NETWORK_PASSPHRASE, PREF_COMMON_DEFAULT_PASSPHRASE) ;
        preferences.putString(PREF_COMMON_NETWORK_IPADDRESS, PREF_COMMON_DEFAULT_IPADDRESS) ;
        preferences.putString(PREF_COMMON_NETWORK_GATEWAY, PREF_COMMON_DEFAULT_GATEWAY) ;
        preferences.putString(PREF_COMMON_NETWORK_MASK, PREF_COMMON_DEFAULT_MASK) ;
        preferences.putString(PREF_COMMON_MODULE_TYPE, PREF_COMMON_DEFAULT_MODULE_TYPE) ;
    }
    Serial.println("Preferences:") ;
    //
    // SSID
    //
    preferences.getString(PREF_COMMON_NETWORK_SSID, strSSID, sizeof(strNetPassphrase));
    Serial.print("\tSSID is -> ") ; Serial.println(strSSID) ;
    //
    //
    // Pass Phrase
    //
    preferences.getString(PREF_COMMON_NETWORK_PASSPHRASE,strNetPassphrase, sizeof(strNetPassphrase)) ;
    Serial.print("\tNetwork Passphrase is -> ") ; Serial.println(strNetPassphrase) ;
    //
    // IP Address
    //
    preferences.getString(PREF_COMMON_NETWORK_IPADDRESS,strIPAddress, sizeof(strIPAddress)) ;
    //
    // Convert the loaded string into a byte array for use by the
    // Wi-Fi configuration code
    //
    parseBytes(strIPAddress, '.', ipAddress, 4, 10) ;   // The input string is base 10
    Serial.print("\tIPAddress is -> ") ; Serial.println(strIPAddress) ;
    //
    // Gateway IP address
    //
    preferences.getString(PREF_COMMON_NETWORK_GATEWAY,strGateway, sizeof(strGateway)) ;
    //
    // Convert the loaded string into a byte array for use by the
    // Wi-Fi configuration code
    //
    parseBytes(strGateway, '.', netGateway, 4, 10) ;   // The input string is base 10
    Serial.print("\tNetwork Gateway is -> ") ; Serial.println(strGateway) ;
     //
    // Network Mask
    //
    preferences.getString(PREF_COMMON_NETWORK_MASK,strNetMask, sizeof(strNetMask)) ;
    //
    // Convert the loaded string into a byte array for use by the
    // Wi-Fi configuration code
    //
    parseBytes(strNetMask, '.', netMask, 4, 10) ;   // The input string is base 10
    Serial.print("\tNetmask is -> ") ; Serial.println(strNetMask) ;
   //
    // Module Type
    //
    preferences.getString(PREF_COMMON_MODULE_TYPE,strModuleType, sizeof(strModuleType)) ;
    Serial.print("\tModule type is -> ") ; Serial.println(strModuleType) ;
    // preferences.remove(PREF_COMMON_NETWORK_SSID) ;  // Temp
    preferences.end() ;

}

//
// This callback function is called each tome the module receives an http command. It checks
// if it is a preferecne related extension command and if it is it executes the command and 
// returns true to indicate the command was processed.
//
// If the passed command is not an API extension command the function returns false and the
// calling code must handle the command.
//

bool preference_change_cb(char *key, char *value)
{
    bool fProcessed = false ;

    if (!strcmp(key, "net_ssid"))
    {
        fProcessed = true ;
    }
    else if (!strcmp(key, "net_ip_address"))
    {
        //
        // Check if the IP address is actually changing, otherwise ignore the
        // command
        //
        if ( strcmp(value, strIPAddress))
        {
            Serial.println("IP Change") ;
            strcpy(strIPAddress, value) ;
            prefs_update_string(PREF_COMMON_NETWORK_IPADDRESS, strIPAddress) ;
        }
        fProcessed = true ;
    }
    else if (!strcmp(key, "net_gateway"))
    {
        fProcessed = true ;
    }
    else if (!strcmp(key, "net_mask"))
    {
        fProcessed = true ;
    }
    if ( fProcessed )
    {
        Serial.printf("API extension command -> command = %s  Value = %s", key, value) ;
    }
    return fProcessed ;
}