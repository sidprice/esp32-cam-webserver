//
// This file contains the definitions used for the ESP32-CAM preferences.
//
// Author: Sid Price
//
// Copyright: Kevin Levesque 2022
//

#pragma once

//
// Define the names of the namespaces of preferences
//
//  N.B. Names may not exceed 15 characters
//

#define PREF_COMMON_SECTION "Common"

//
// Define the names of the keys in each of the above sections
//
//  N.B. Names may not exceed 15 characters
//  

// Common
#define PREF_COMMON_NETWORK_SSID        "Net_SSID"
#define PREF_COMMON_NETWORK_PASSPHRASE  "Net_Pass"
#define PREF_COMMON_NETWORK_IPADDRESS   "Net_IP"
#define PREF_COMMON_NETWORK_MASK        "Net_Mask"
#define PREF_COMMON_MODULE_TYPE         "Module_Type"

//
// Define the factory reset values for the preferences
//

//  Common
#define PREF_COMMON_DEFAULT_SSID        "Avian Ambassadors"
#define PREF_COMMON_DEFAULT_PASSPHRASE  "mijo498rocks"      // Place the SSID pass phrase here if network is secure
#define PREF_COMMON_DEFAULT_IPADDRESS   "192.168.1.254"
#define PREF_COMMON_DEFAULT_MASK        "255.255.0.0"

//
// Edit the variable value below to define the module type being built
//
#define PREF_COMMON_DEFAULT_MODULE_TYPE "ESP32-CAM"