#ifndef _HEX_PREF_H_
#define _HEX_PREF_H_
HEX_BEGIN

#define HEX_PREFERENCES_FILEPATH "preferences.ini"
#define HEX_LOADORDER_FILEPATH "loadorder.ini"

HEX_API extern bool InitializePreferences();
HEX_API extern bool UninitializePreferences();

HEX_API extern bool InitializeLoadOrder();
HEX_API extern bool UninitializeLoadOrder();
	
HEX_END
#endif