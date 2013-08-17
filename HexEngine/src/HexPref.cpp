#include "../include/HexMain.h"

#ifdef _HEX_PREF_H_
HEX_BEGIN

#define HEX_PREFERENCE_SCREENWIDTH "ScreenWidth"
#define HEX_PREFERENCE_SCREENHEIGHT "ScreenHeight"
#define HEX_PREFERENCE_RENDERWIDTH "RenderWidth"
#define HEX_PREFERENCE_RENDERHEIGHT "RenderHeight"
#define HEX_PREFERENCE_LUMINANCEWIDTH "LuminanceWidth"
#define HEX_PREFERENCE_LUMINANCEHEIGHT "LuminanceHeight"
#define HEX_PREFERENCE_SHADOWMAPWIDTH "ShadowMapWidth"
#define HEX_PREFERENCE_SHADOWMAPHEIGHT "ShadowMapHeight"
#define HEX_PREFERENCE_AOFILTERRADIUS "AOFilterRadius"
#define HEX_PREFERENCE_EYEBRIDGEWIDTH "EyeBridgeWidth"
#define HEX_PREFERENCE_GAMMA "Gamma"
#define HEX_PREFERENCE_RANDOMFILTERSIZE "RandomFilterSize"
#define HEX_PREFERENCE_MAXPOINTLIGHTS "MaxPointLights"
#define HEX_PREFERENCE_ENABLESHADOW "EnableShadow"
#define HEX_PREFERENCE_ENABLELUMINANCE "EnableLuminance"
#define HEX_PREFERENCE_ENABLEAMBIENTOCCLUSION "EnableAmbientOcclusion"

FILE* PrefrencesFile = NULL;

void OutputDefaultPreferences()
{
	if (PrefrencesFile != NULL) return;
	fopen_s(&PrefrencesFile, HEX_PREFERENCES_FILEPATH, "w");

	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_SCREENWIDTH, ScreenRect.width);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_SCREENHEIGHT, ScreenRect.height);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_RENDERWIDTH, RenderRect.width);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_RENDERHEIGHT, RenderRect.height);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_LUMINANCEWIDTH, LuminanceRect.width);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_LUMINANCEHEIGHT, LuminanceRect.height);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_SHADOWMAPWIDTH, ShadowRect.width);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_SHADOWMAPHEIGHT, ShadowRect.height);
	fprintf(PrefrencesFile, "\n");
	fprintf(PrefrencesFile, "%s = %f\n", HEX_PREFERENCE_AOFILTERRADIUS, AOFilterRadius);
	fprintf(PrefrencesFile, "%s = %f\n", HEX_PREFERENCE_EYEBRIDGEWIDTH, EyeBridgeWidth);
	fprintf(PrefrencesFile, "%s = %f\n", HEX_PREFERENCE_GAMMA, Gamma);
	fprintf(PrefrencesFile, "\n");
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_RANDOMFILTERSIZE, RandomFilterSize);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_MAXPOINTLIGHTS, MaxPointLights);
	fprintf(PrefrencesFile, "\n");
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_ENABLESHADOW, EnableShadow);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_ENABLELUMINANCE, EnableLuminance);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_ENABLEAMBIENTOCCLUSION, EnableAmbientOcclusion);
}
	
HEX_API bool InitializePreferences()
{
	fopen_s(&PrefrencesFile, HEX_PREFERENCES_FILEPATH, "r");
	if (PrefrencesFile == NULL) OutputDefaultPreferences();
	fclose(PrefrencesFile);

	MALib::TEXTFILE* pref = 0;
	if (!MALib::ImportTextFile(HEX_PREFERENCES_FILEPATH, &pref)) return false;
	
	uint screenWidth = ScreenRect.width;
	uint screenHeight = ScreenRect.height;
	uint renderWidth = RenderRect.width;
	uint renderHeight = RenderRect.height;
	uint luminanceWidth = LuminanceRect.width;
	uint luminanceHeight = LuminanceRect.height;
	uint shadowWidth = ShadowRect.width;
	uint shadowHeight = ShadowRect.height;
	float aoFilterRadius = AOFilterRadius;
	float eyeBridgeWidth = EyeBridgeWidth;
	float gamma = Gamma;
	uint randomFilterSize = RandomFilterSize;
	uint maxPointLights = MaxPointLights;
	uint enableShadow = EnableShadow;
	uint enableLuminance = EnableLuminance;
	uint enableAmbientOcclusion = EnableAmbientOcclusion;

	for (uint i = 0; i < pref->lines.length(); i++)
	{
		string line = pref->lines[i];

		if (strstr(line, HEX_PREFERENCE_SCREENWIDTH) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &screenWidth);
		}
		else if (strstr(line, HEX_PREFERENCE_SCREENHEIGHT) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &screenHeight);
		}
		else if (strstr(line, HEX_PREFERENCE_RENDERWIDTH) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &renderWidth);
		}
		else if (strstr(line, HEX_PREFERENCE_RENDERHEIGHT) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &renderHeight);
		}
		else if (strstr(line, HEX_PREFERENCE_LUMINANCEWIDTH) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &luminanceWidth);
		}
		else if (strstr(line, HEX_PREFERENCE_LUMINANCEHEIGHT) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &luminanceHeight);
		}
		else if (strstr(line, HEX_PREFERENCE_SHADOWMAPWIDTH) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &shadowWidth);
		}
		else if (strstr(line, HEX_PREFERENCE_SHADOWMAPHEIGHT) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &shadowHeight);
		}
		else if (strstr(line, HEX_PREFERENCE_AOFILTERRADIUS) != 0)
		{
			string check = strpbrk(line, ".0123456789");
			sscanf(check, "%f", &aoFilterRadius);
		}
		else if (strstr(line, HEX_PREFERENCE_EYEBRIDGEWIDTH) != 0)
		{
			string check = strpbrk(line, ".0123456789");
			sscanf(check, "%f", &eyeBridgeWidth);
		}
		else if (strstr(line, HEX_PREFERENCE_GAMMA) != 0)
		{
			string check = strpbrk(line, ".0123456789");
			sscanf(check, "%f", &gamma);
		}
		else if (strstr(line, HEX_PREFERENCE_RANDOMFILTERSIZE) != 0)
		{
			string check = strpbrk(line, ".0123456789");
			sscanf(check, "%f", &randomFilterSize);
		}
		else if (strstr(line, HEX_PREFERENCE_MAXPOINTLIGHTS) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &maxPointLights);
		}
		else if (strstr(line, HEX_PREFERENCE_ENABLESHADOW) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &enableShadow);
		}
		else if (strstr(line, HEX_PREFERENCE_ENABLELUMINANCE) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &enableLuminance);
		}
		else if (strstr(line, HEX_PREFERENCE_ENABLEAMBIENTOCCLUSION) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &enableAmbientOcclusion);
		}
	}

	AspectRatio = float(screenWidth) / float(screenHeight);
	ScreenRect = MALib::RECT(screenWidth, screenHeight);
	RenderRect = MALib::RECT(renderWidth, renderHeight);
	LuminanceRect = MALib::RECT(luminanceWidth, luminanceHeight);
	ShadowRect = MALib::RECT(shadowWidth, shadowHeight);
	AOFilterRadius = aoFilterRadius;
	EyeBridgeWidth = eyeBridgeWidth;
	Gamma = gamma;
	RandomFilterSize = randomFilterSize;
	MaxPointLights = maxPointLights;
	EnableShadow = enableShadow != 0;
	EnableLuminance = enableLuminance != 0;
	EnableAmbientOcclusion = enableAmbientOcclusion != 0;

	return true;
}
HEX_API bool UninitializePreferences()
{
	return true;
}

HEX_API bool InitializeLoadOrder()
{
	MALib::TEXTFILE* load = 0;
	
	if (!MALib::ImportTextFile(HEX_LOADORDER_FILEPATH, &load))
	{
		MALib::CreateTextFile(&load, 0, 0);
		MALib::ExportTextFile(HEX_LOADORDER_FILEPATH, load);
	}

	for (uint i = 0; i < load->lines.length(); i++)
	{
		Scene* scene = LoadScene(load->lines[i]);
		if (scene == 0) continue;
		
		Scenes.add(scene);
		if (!BuildScene(Scenes[i]))
		{
			MALib::LOG_Message("Could not build scene.", load->lines[i]);
			return false;
		}
	}

	MALib::FreeTextFile(&load);
	
	return true;
}
HEX_API bool UninitializeLoadOrder()
{
	return true;
}
	
HEX_END
#endif