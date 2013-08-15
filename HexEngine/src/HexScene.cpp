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
	
typedef struct Prefab
{
	Prefab()
	{
		memset(this, 0, sizeof(Prefab));
	}
	~Prefab()
	{
#if 0
		//if (this->name != 0) delete [] this->name;
		if (this->data.mesh != 0) delete [] this->data.mesh;
		if (this->data.diffuse != 0) delete [] this->data.diffuse;
		if (this->data.normal != 0) delete [] this->data.normal;
		if (this->data.specular != 0) delete [] this->data.specular;
#endif
#if 0
		this->commands.clear();
		this->children.clear();
#endif
		memset(this, 0, sizeof(Prefab));
	}
	string name;
	struct
	{
		string mesh;
		string diffuse;
		string normal;
		string specular;
	} data;
	//uint filepathBufferSize;
	MALib::ARRAY<string> commands;
	MALib::ARRAY<Prefab> children;
} Prefab;
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
	MALib::ARRAY<Prefab> prefabs;
	MALib::ARRAY<string> commands;
	MALib::ARRAY<string> loadOrder;
	MALib::TEXTFILE* file;
} Scene;

void GetPrefab(string name, MALib::ARRAY<Prefab>& list, Prefab* outPrefab)
{
	if (name == 0 || list.length() < 1 || outPrefab == 0) return;

	for (uint i = 0; i < list.length(); i++)
	{
		Prefab prefab = list[i];
		if (strcmp(prefab.name, name) == 0)
		{
			*outPrefab = prefab;
			return;
		}
	}
}
Scene* CreateScene(string filepath)
{
	if (filepath == 0) return 0;
	
	if (GetFiletype(filepath) != FILETYPE_SCENE) return 0;
	MALib::TEXTFILE* file = 0;
	if (!MALib::ImportTextFile(filepath, &file)) return 0;

	Scene* scene = new Scene;
	memset(scene, 0, sizeof(Scene));

	scene->unitSize = 1.0f;
	scene->prefabs.resize(64);
	scene->commands.resize(64);
	scene->loadOrder.resize(64);
	scene->file = file;

	return scene;
}

bool ParseFilepath(string str, string* outBuffer)
{
	if (str == 0 || outBuffer == 0) return false;

	string filepath = strchr(str, '\"') + 1;
	size_t span = strcspn(filepath, "\"");
	if (span < 1) return false;
	
	/**outBuffer = new char[span];
	memset(*outBuffer, 0, sizeof(char) * 256);

	strcpy(*outBuffer, filepath);
	*outBuffer[span] = '\0';*/
	filepath[span] = '\0';
	*outBuffer = filepath;
	return true;
}
bool ParseMesh(string str, uint* outMesh)
{
	string filepath = 0;
	ParseFilepath(str, &filepath);
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
	ParseFilepath(str, &filepath);
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
	if (str == 0) return false;
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
	static Prefab currentPrefab;
	static bool foundPrefab = false;
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
		//CreatePrefab(str, &currentPrefab);
		currentPrefab = Prefab();
		currentPrefab.name = check;
		foundPrefab = true;
		return true;
	}
	check = 0;
	check = strchr(str, '{');
	if (check != 0)
	{
		if (!foundPrefab) return false;
		insidePrefab = true;
		return true;
	}
	check = 0;
	check = strchr(str, '}');
	if (check != 0)
	{
		if (!foundPrefab) return false;
		if (!insidePrefab) return false;
		insidePrefab = false;
		scene->prefabs.add(currentPrefab);
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
	check = 0;
	check = strstr(str, COMMAND_PARENT);
	if (check != 0)
	{
		check += strlen(COMMAND_PARENT) + 1;
		if (!insidePrefab) return false;
		Prefab child;
		GetPrefab(check, scene->prefabs, &child);
		currentPrefab.children.add(child);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_VERTEXMAP);
	if (check != 0)
	{
		check += strlen(COMMAND_VERTEXMAP) + 1;
		if (!insidePrefab) return false;
		ParseFilepath(check, &currentPrefab.data.mesh);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_DIFFUSE);
	if (check != 0)
	{
		check += strlen(COMMAND_DIFFUSE) + 1;
		if (!insidePrefab) return false;
		ParseFilepath(check, &currentPrefab.data.diffuse);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_NORMAL);
	if (check != 0)
	{
		check += strlen(COMMAND_NORMAL) + 1;
		if (!insidePrefab) return false;
		ParseFilepath(check, &currentPrefab.data.normal);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_SPECULAR);
	if (check != 0)
	{
		check += strlen(COMMAND_SPECULAR) + 1;
		if (!insidePrefab) return false;
		ParseFilepath(check, &currentPrefab.data.specular);
		return true;
	}
	if (IsCommand(str))
	{
		if (insidePrefab) currentPrefab.commands.add(str);
		else scene->commands.add(str);
		return true;
	}
	return true;
}

void LogPrefab(Prefab* prefab)
{
	if (prefab == 0) return;
	MALib::LOG_Message("PREFAB NAME", prefab->name);
	MALib::LOG_Message("VERTEX MAP", prefab->data.mesh);
	MALib::LOG_Message("DIFFUSE", prefab->data.diffuse);
	MALib::LOG_Message("NORMAL", prefab->data.normal);
	MALib::LOG_Message("SPECULAR", prefab->data.specular);
	for (uint i = 0; i < prefab->commands.length(); i++) MALib::LOG_Message("COMMAND", prefab->commands[i]);
	for (uint i = 0; i < prefab->children.length(); i++)
	{
		MALib::LOG_Message("CHILD");
		LogPrefab(&prefab->children[i]);
	}
}

HEX_API bool LoadScene(const string filepath)
{
	if (filepath == 0) return false;

	Scene* scene = CreateScene(filepath);
	if (scene == 0) return false;

	bool foundError = false;
	uint count = 0;
	for (uint i = 0; i < scene->file->lines.length(); i++)
	{
		string line = scene->file->lines[i];
		count = i;

		if (strlen(line) < 1) continue;

		foundError = !ParseLine(line, scene);
		if (foundError) break;
	}

	MALib::LOG_Message("SCENE PREFABS");
	for (uint i = 0; i < scene->prefabs.length(); i++)
	{
		Prefab* prefab = &scene->prefabs[i];
		LogPrefab(prefab);
	}
	MALib::LOG_Message("SCENE COMMANDS");
	for (uint i = 0; i < scene->commands.length(); i++) MALib::LOG_Message("COMMAND", scene->commands[i]);
	MALib::LOG_Message("SCENE LOAD ORDER");
	for (uint i = 0; i < scene->loadOrder.length(); i++) MALib::LOG_Message("PREFAB", scene->loadOrder[i]);

	if (foundError) MALib::LOG_Out1i("FAILED TO LOAD SCENE, ERROR ON LINE :", count + 1);
	return !foundError;
}

HEX_END
#endif