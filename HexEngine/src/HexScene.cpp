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
	
#define COMMAND_UNITSIZE "UNIT_SIZE"
#define COMMAND_CREATEPREFAB "prefab"
#define COMMAND_PARENT "parent"
#define COMMAND_LOAD "load"
	
typedef struct Scene
{
	~Scene()
	{
		this->prefabs.clear();
		this->commands.clear();
		this->loadOrder.clear();
		if (this->file != 0) MALib::FreeTextFile(&this->file);
	}
	float unitSize;
	MALib::ARRAY<Prefab*> prefabs;
	MALib::ARRAY<string> commands;
	MALib::ARRAY<string> loadOrder;
	MALib::TEXTFILE* file;
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
	uint filepathBufferSize;
	MALib::ARRAY<string> commands;
	MALib::ARRAY<Prefab> children;
} Prefab;

Prefab* GetPrefab(string name, Scene* scene)
{
	if (name == 0 || scene == 0) return 0;

	for (uint i = 0; i < scene->prefabs.length(); i++)
	{
		Prefab* prefab = scene->prefabs[i];
		if (prefab == 0) continue;
		if (strcmp(prefab->name, name) == 0) return prefab;
	}
	return 0;
}
Scene* CreateScene(string filepath)
{
}
Prefab* CreatePrefab(string name)
{
	Prefab* prefab = new Prefab;
	memset(prefab, 0, sizeof(Prefab));

	prefab->name = name;

	prefab->filepathBufferSize = 64;
	prefab->data.mesh = new char[prefab->filepathBufferSize];
	prefab->data.diffuse = new char[prefab->filepathBufferSize];
	prefab->data.normal = new char[prefab->filepathBufferSize];
	prefab->data.specular = new char[prefab->filepathBufferSize];
	memset(prefab->data.mesh, 0, sizeof(char) * prefab->filepathBufferSize);
	memset(prefab->data.diffuse, 0, sizeof(char) * prefab->filepathBufferSize);
	memset(prefab->data.normal, 0, sizeof(char) * prefab->filepathBufferSize);
	memset(prefab->data.specular, 0, sizeof(char) * prefab->filepathBufferSize);
	prefab->commands.resize(8);
	prefab->children.resize(8);

	return prefab;
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
bool ParseLine(string str, Scene* scene)
{
	if (str == 0 || scene == 0) return false;
	string check = 0;
	static Prefab* currentPrefab = 0;
	static bool insidePrefab = false;
	check = strstr(str, COMMAND_UNITSIZE);
	if (check != 0)
	{
		check += strlen(COMMAND_UNITSIZE) + 1;
		sscanf(check, "%f", &scene->unitSize);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_CREATEPREFAB);
	if (check != 0)
	{
		check += strlen(COMMAND_CREATEPREFAB) + 1;
		CreatePrefab(str, currentPrefab);
		return true;
	}
	check = 0;
	check = strchr(str, '{');
	if (check != 0)
	{
		if (currentPrefab == 0) return false;
		insidePrefab = true;
		return true;
	}
	check = 0;
	check = strchr(str, '}');
	if (check != 0)
	{
		if (!insidePrefab) return false;
		insidePrefab = false;
		currentPrefab = 0;
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_LOAD);
	if (check != 0)
	{
		check += strlen(COMMAND_LOAD) + 1;
		scene->loadOrder.add(check);
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

	Scene scene;
	scene.unitSize = 1.0f;
	scene.prefabs.resize(64);
	scene.commands.resize(64);
	scene.loadOrder.resize(64);
	scene.file = file;

	bool foundError = false;
	for (uint i = 0; i < file->lines.length(); i++)
	{
		string line = file->lines[i];

		if (strlen(line) < 1) continue;

		foundError = !ParseLine(line, &scene);
		if (foundError) break;
	}
	return !foundError;
}

HEX_END
#endif