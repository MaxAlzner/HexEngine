#ifndef _HEX_PREF_H_
#define _HEX_PREF_H_
HEX_BEGIN

#define HEX_VERTEXSHADER_FILEPATH "data/gl_shader.vert"
#define HEX_FRAGMENTSHADER_FILEPATH "data/gl_shader.frag"

#define HEX_SHADER_PREFERENCE_FORMAT '%'

#define HEX_PREFERENCES_FILEPATH "preferences.ini"
#define HEX_LOADORDER_FILEPATH "loadorder.ini"

#define HEX_PREFERENCE_SCREENWIDTH "ScreenWidth"
#define HEX_PREFERENCE_SCREENHEIGHT "ScreenHeight"
#define HEX_PREFERENCE_RENDERWIDTH "RenderWidth"
#define HEX_PREFERENCE_RENDERHEIGHT "RenderHeight"
#define HEX_PREFERENCE_LUMINANCESIZE "LuminanceSize"
#define HEX_PREFERENCE_SHADOWMAPSIZE "ShadowMapSize"
#define HEX_PREFERENCE_BLOOMFILTERRADIUS "BloomFilterRadius"
#define HEX_PREFERENCE_AOFILTERRADIUS "AOFilterRadius"
#define HEX_PREFERENCE_EYEBRIDGEWIDTH "EyeBridgeWidth"
#define HEX_PREFERENCE_GAMMA "Gamma"
#define HEX_PREFERENCE_RANDOMFILTERSIZE "RandomFilterSize"
#define HEX_PREFERENCE_MAXPOINTLIGHTS "MaxPointLights"
#define HEX_PREFERENCE_ENABLESHADOW "EnableShadow"
#define HEX_PREFERENCE_ENABLELUMINANCE "EnableLuminance"
#define HEX_PREFERENCE_ENABLEAMBIENTOCCLUSION "EnableAmbientOcclusion"

HEX_API extern bool InitializePreferences();
HEX_API extern bool UninitializePreferences();

HEX_API extern bool InitializeLoadOrder();
HEX_API extern bool UninitializeLoadOrder();
	
HEX_END
#endif