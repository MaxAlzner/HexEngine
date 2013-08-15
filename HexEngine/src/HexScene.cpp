#include "..\include\HexMain.h"

#ifdef _HEX_SCENE_H_
HEX_BEGIN

#define COMMAND_TRANSLATE "translate"
#define COMMAND_ROTATE "rotate"
#define COMMAND_SCALE "scale"
#define COMMAND_STATIC "static"
#define COMMAND_OVERLAY "overlay"
#define COMMAND_SPECULAR "specular"
#define COMMAND_UVREPEAT "uvrepeat"
#define COMMAND_UVOFFSET "uvoffset"
#define COMMAND_CASTER "caster"
	
#define COMMAND_VERTEXMAP "vertexMap"
#define COMMAND_DIFFUSE "diffuse"
#define COMMAND_NORMAL "normal"
#define COMMAND_SPECULAR "specular"

#define COMMAND_PARENT "parent"
#define COMMAND_LOAD "load"
	
typedef struct Scene
{
	float unitSize;
	MALib::ARRAY<Prefab> prefabs;
	MALib::ARRAY<string> commands;
} Scene;
typedef struct Prefab
{
	~Prefab()
	{
		this->commands.clear();
		this->children.clear();
	}
	string name;
	struct
	{
		string mesh;
		string diffuse;
		string normal;
		string specular;
	} data;
	uint bufferSize;
	MALib::ARRAY<string> commands;
	MALib::ARRAY<Prefab> children;
} Prefab;

void CreatePrefab(string str, Prefab* prefab)
{
	if (prefab == 0) return;
	
	memset(prefab, 0, sizeof(Prefab));
	prefab->bufferSize = 64;
	prefab->name = new char[prefab->bufferSize];
	prefab->data.mesh = new char[prefab->bufferSize];
	prefab->data.diffuse = new char[prefab->bufferSize];
	prefab->data.normal = new char[prefab->bufferSize];
	prefab->data.specular = new char[prefab->bufferSize];
	memset(prefab->data.mesh, 0, sizeof(char) * prefab->bufferSize);
	memset(prefab->data.diffuse, 0, sizeof(char) * prefab->bufferSize);
	memset(prefab->data.normal, 0, sizeof(char) * prefab->bufferSize);
	memset(prefab->data.specular, 0, sizeof(char) * prefab->bufferSize);
	prefab->commands.resize(8);
	prefab->children.resize(8);
}

bool ParseFilepath(string str, string buffer, uint size)
{
	if (str == 0 || buffer == 0) return false;
	
	memset(buffer, 0, sizeof(char) * 256);

	string filepath = strchr(str, '\"') + 1;
	size_t span = strcspn(filepath, "\"");
	if (span < 1) return false;

	strcpy(buffer, filepath);
	buffer[span] = '\0';
	return true;
}
bool ParseMesh(string str, uint* outMesh)
{
	string filepath = 0;
	ParseFilepath(str, filepath, 0);
	if (filepath == 0)
	{
		return false;
	}
	FILETYPE type = GetFiletype(filepath);
	if      (type == FILETYPE_OBJ) RegisterOBJ(outMesh, filepath);
	else if (type == FILETYPE_VMP) RegisterVMP(outMesh, filepath);
	else
	{
		return false;
	}
	return true;
}
bool ParseTexture(string str, uint* outTex)
{
	string filepath = 0;
	ParseFilepath(str, filepath, 0);
	if (filepath == 0)
	{
		return false;
	}
	FILETYPE type = GetFiletype(filepath);
	if      (type == FILETYPE_BMP) RegisterBMP(outTex, filepath);
	else if (type == FILETYPE_TGA) RegisterTGA(outTex, filepath);
	else
	{
		return false;
	}
	return true;
}
void ParseVector(string str, float* v0, float* v1, float* v2)
{
	sscanf(str, "%f %f %f", v0, v1, v2);
}
void ParseVector(string str, float* v0, float* v1)
{
	sscanf(str, "%f %f", v0, v1);
}
bool ParseBoolean(string str)
{
	char* check = strstr(str, "true");
	if (check == 0) return false;
	return true;
}

bool ParseCommand(string str)
{
	if (str == 0 || BoundEntity == 0) return false;
	string check = 0;
	check = strstr(str, COMMAND_TRANSLATE);
	if (check != 0)
	{
		check += strlen(COMMAND_TRANSLATE) + 1;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		ParseVector(check, &x, &y, &z);
		BoundEntity->transform->translate(x, y, z);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_ROTATE);
	if (check != 0)
	{
		check += strlen(COMMAND_ROTATE) + 1;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		ParseVector(check, &x, &y, &z);
		BoundEntity->transform->rotate(x, y, z);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_SCALE);
	if (check != 0)
	{
		check += strlen(COMMAND_SCALE) + 1;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		ParseVector(check, &x, &y, &z);
		BoundEntity->transform->scale(x, y, z);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_STATIC);
	if (check != 0)
	{
		check += strlen(COMMAND_STATIC) + 1;
		BoundEntity->makeStatic(ParseBoolean(check));
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_OVERLAY);
	if (check != 0)
	{
		check += strlen(COMMAND_OVERLAY) + 1;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		ParseVector(check, &x, &y, &z);
		BoundEntity->material->setOverlay(x, y, z);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_SPECULAR);
	if (check != 0)
	{
		check += strlen(COMMAND_SPECULAR) + 1;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		ParseVector(check, &x, &y, &z);
		BoundEntity->material->setSpecular(x, y, z);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_UVREPEAT);
	if (check != 0)
	{
		check += strlen(COMMAND_UVREPEAT) + 1;
		float u = 0.0f;
		float v = 0.0f;
		ParseVector(check, &u, &v);
		BoundEntity->material->repeatUV(u, v);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_UVOFFSET);
	if (check != 0)
	{
		check += strlen(COMMAND_UVOFFSET) + 1;
		float u = 0.0f;
		float v = 0.0f;
		ParseVector(check, &u, &v);
		BoundEntity->material->offsetUV(u, v);
		return true;
	}
	check = strstr(str, COMMAND_CASTER);
	if (check != 0)
	{
		check += strlen(COMMAND_CASTER) + 1;
		BoundEntity->material->makeCaster(ParseBoolean(check));
		return true;
	}
	return false;
}
bool IsCommand(string str)
{
	if (str == 0 || BoundEntity == 0) return false;
	string check = 0;
	check = strstr(str, COMMAND_TRANSLATE);
	if (check != 0)
	{
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_ROTATE);
	if (check != 0)
	{
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_SCALE);
	if (check != 0)
	{
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_STATIC);
	if (check != 0)
	{
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_OVERLAY);
	if (check != 0)
	{
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_SPECULAR);
	if (check != 0)
	{
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_UVREPEAT);
	if (check != 0)
	{
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_UVOFFSET);
	if (check != 0)
	{
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_CASTER);
	if (check != 0)
	{
		return true;
	}
	return false;
}

HEX_API bool LoadScene(const string filepath)
{
	if (filepath == 0) return false;
	if (GetFiletype(filepath) != FILETYPE_SCENE) return false;
	MALib::TEXTFILE* file = 0;
	if (!MALib::ImportTextFile(filepath, &file)) return false;
	bool result = LoadScene(file);
	MALib::FreeTextFile(&file);
	return result;
}
HEX_API bool LoadScene(MALib::TEXTFILE* file)
{
	if (file == 0) return false;
	Scene scene;
	scene.unitSize = 1.0f;
	scene.prefabs.resize(64);
	scene.commands.resize(64);

	bool foundError = false;
	bool foundPrefab = false;
	bool enteredPrefab = false;
	Prefab* currentPrefab = 0;
	static char scratch[256];
	memset(scratch, 0, sizeof(char) * 256);
	for (uint i = 0; i < file->lines.length(); i++)
	{
		memset(scratch, 0, sizeof(char) * 256);
		string line = file->lines[i];

		if (strlen(line) < 1) continue;
		sscanf(line, "%s", scratch);

		if (strcmp(scratch, "UNIT_SIZE") == 0)
		{
			sscanf(line, "UNIT_SIZE %f", &scene.unitSize);
		}
		else if (strcmp(scratch, "prefab") == 0)
		{
			foundPrefab = true;
			CreatePrefab(line, currentPrefab);
			scene.prefabs.add(*currentPrefab);
		}
		else if (strcmp(scratch, "{") == 0)
		{
			if (currentPrefab == 0)
			{
				foundError = true;
				break;
			}
			enteredPrefab = true;
		}
		else if (strcmp(scratch, "}") == 0)
		{
			currentPrefab = 0;
			enteredPrefab = false;
		}
	}
	delete [] scratch;
	return !foundError;
}

HEX_END
#endif