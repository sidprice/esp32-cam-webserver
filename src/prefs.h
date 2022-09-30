//
// ESP32 Module Preference handling.
//
// Author Sid Price
//
// Copyright Kevin Levesque 2022
//

#pragma Once

extern byte ipAddress[] ;
extern byte netGateway[] ;
extern byte netMask[] ;
extern char strSSID[] ;
extern char strNetPassphrase[] ;

void prefs_get_preferences(bool factoryReset) ;
void prefs_update_preferences(void) ;
bool preference_change_cb(char *key, char *value) ;