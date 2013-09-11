#include "../include/HexMain.h"

#ifdef _HEX_PREF_H_
HEX_BEGIN

FILE* PrefrencesFile = NULL;

void OutputDefaultPreferences()
{
	if (PrefrencesFile != NULL) return;
	fopen_s(&PrefrencesFile, HEX_PREFERENCES_FILEPATH, "w");

	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_SCREENWIDTH, ScreenRect.width);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_SCREENHEIGHT, ScreenRect.height);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_RENDERWIDTH, RenderRect.width);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_RENDERHEIGHT, RenderRect.height);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_LUMINANCESIZE, LuminanceRect.width);
	fprintf(PrefrencesFile, "%s = %d\n", HEX_PREFERENCE_SHADOWMAPSIZE, ShadowRect.width);
	fprintf(PrefrencesFile, "\n");
	fprintf(PrefrencesFile, "%s = %f\n", HEX_PREFERENCE_BLOOMFILTERRADIUS, BloomFilterRadius);
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

bool InsertPreference(string* dest, string preference)
{
	if (dest == NULL || preference == NULL) return false;

	static char scratch[4];
	memset(scratch, 0, sizeof(char) * 4);
	if (strcmp(preference, HEX_PREFERENCE_RANDOMFILTERSIZE) == 0)
	{
		sprintf(scratch, "%d", RandomFilterSize);
	}
	else if (strcmp(preference, HEX_PREFERENCE_MAXPOINTLIGHTS) == 0)
	{
		sprintf(scratch, "%d", MaxPointLights);
	}
	else return false;
	
	for (uint i = 0; i < 4; i++)
	{
		char ch = scratch[i];
		if (ch == '\0') break;
		*(*dest) = ch;
		*dest += 1;
	}
	return true;
}
bool FormatShader(string* src, string* dest)
{
	if (src == NULL || dest == NULL) return false;
	
	string output = *dest;
	string read = *src;
	uint index = 0;
	static char scratch[32];
	while (index < FragmentShader->size)
	{
		char ch = *read;
		if (ch == '\0') break;
		read++;
		if (ch == HEX_SHADER_PREFERENCE_FORMAT)
		{
			memset(scratch, 0, sizeof(char) * 32);
			for (uint i = 0; i < 32; i++)
			{
				ch = read[i];
				if (ch == '\0' || ch == HEX_SHADER_PREFERENCE_FORMAT) break;
				scratch[i] = ch;
			}
			string end = strchr(read + 1, HEX_SHADER_PREFERENCE_FORMAT);
			if (!InsertPreference(&output, scratch)) return false;
			read = end + 1;
		}
		else
		{
			*output = ch;
			output++;
		}
	}

	return true;
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
	uint luminanceSize = LuminanceRect.width;
	uint shadowSize = ShadowRect.width;
	float bloomFilterRadius = BloomFilterRadius;
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
		else if (strstr(line, HEX_PREFERENCE_LUMINANCESIZE) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &luminanceSize);
		}
		else if (strstr(line, HEX_PREFERENCE_LUMINANCESIZE) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &luminanceSize);
		}
		else if (strstr(line, HEX_PREFERENCE_SHADOWMAPSIZE) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &shadowSize);
		}
		else if (strstr(line, HEX_PREFERENCE_SHADOWMAPSIZE) != 0)
		{
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &shadowSize);
		}
		else if (strstr(line, HEX_PREFERENCE_BLOOMFILTERRADIUS) != 0)
		{
			string check = strpbrk(line, ".0123456789");
			sscanf(check, "%f", &bloomFilterRadius);
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
			string check = strpbrk(line, "0123456789");
			sscanf(check, "%d", &randomFilterSize);
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
	LuminanceRect = MALib::RECT(luminanceSize, luminanceSize);
	ShadowRect = MALib::RECT(shadowSize, shadowSize);
	BloomFilterRadius = bloomFilterRadius;
	AOFilterRadius = aoFilterRadius;
	EyeBridgeWidth = eyeBridgeWidth;
	Gamma = gamma;
	RandomFilterSize = randomFilterSize;
	MaxPointLights = maxPointLights;
	EnableShadow = enableShadow != 0;
	EnableLuminance = enableLuminance != 0;
	EnableAmbientOcclusion = enableAmbientOcclusion != 0;

	if (VertexShader != NULL)
	{
		VertexShaderSource = new char[VertexShader->size];
		memset(VertexShaderSource, 0, sizeof(char) * VertexShader->size);
		if (!FormatShader(&VertexShader->data, &VertexShaderSource)) return false;
	}
	if (FragmentShader != NULL)
	{
		FragmentShaderSource = new char[FragmentShader->size];
		memset(FragmentShaderSource, 0, sizeof(char) * FragmentShader->size);
		if (!FormatShader(&FragmentShader->data, &FragmentShaderSource)) return false;
	}

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

	ClearGame();
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