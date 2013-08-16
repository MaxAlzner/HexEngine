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
	
#define COMMAND_CAMERANODE "camera"
#define COMMAND_LIGHTNODE "light"
#define COMMAND_CONTROLNODE "controller"
	
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
	~Prefab()
	{
		this->children.clear();
		this->commands.clear();
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
	MALib::ARRAY<Prefab*> children;
	MALib::ARRAY<string> commands;
} Prefab;
typedef struct Scene
{
	~Scene()
	{
		this->prefabs.clear();
		this->loadOrder.clear();
		if (this->file != 0) MALib::FreeTextFile(&this->file);
	}
	float unitSize;
	MALib::ARRAY<Prefab*> prefabs;
	MALib::ARRAY<Prefab*> loadOrder;
	MALib::TEXTFILE* file;
} Scene;

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
		LogPrefab(prefab->children[i]);
	}
}
void LogScene(Scene* scene)
{
	if (scene == 0) return;
	MALib::LOG_Message(" ");
	MALib::LOG_Out1f("SCENE UNIT SIZE", scene->unitSize);
	MALib::LOG_Message(" ");
	MALib::LOG_Message("SCENE PREFABS");
	for (uint i = 0; i < scene->prefabs.length(); i++)
	{
		Prefab* prefab = scene->prefabs[i];
		LogPrefab(prefab);
		MALib::LOG_Message(" ");
	}
	MALib::LOG_Message("SCENE LOAD ORDER");
	for (uint i = 0; i < scene->loadOrder.length(); i++)
	{
		LogPrefab(scene->loadOrder[i]);
		MALib::LOG_Message(" ");
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
	scene->prefabs.resize(32);
	scene->loadOrder.resize(64);
	scene->file = file;

	return scene;
}
Prefab* CreatePrefab(string name)
{
	Prefab* prefab = new Prefab;
	memset(prefab, 0, sizeof(Prefab));

	prefab->name = name;
	prefab->commands.resize(8);
	prefab->children.resize(8);

	return prefab;
}
Prefab* GetPrefab(string name, MALib::ARRAY<Prefab*>& list)
{
	if (name == 0 || list.length() < 1) return 0;

	for (uint i = 0; i < list.length(); i++)
	{
		Prefab* prefab = list[i];
		if (prefab->name == 0) continue;
		if (strcmp(prefab->name, name) == 0)
		{
			return prefab;
		}
	}
	return 0;
}
void CopyPrefab(Prefab* dest, Prefab* src)
{
	if (dest == 0 || src == 0) return;

	dest->name = src->name;
	dest->data.mesh = src->data.mesh;
	dest->data.diffuse = src->data.diffuse;
	dest->data.normal = src->data.normal;
	dest->data.specular = src->data.specular;
	for (uint i = 0; i < src->commands.length(); i++) dest->commands.add(src->commands[i]);
	for (uint i = 0; i < src->children.length(); i++)
	{
		Prefab* srcChild = src->children[i];
		if (srcChild == 0) continue;
		Prefab* destChild = CreatePrefab(0);
		CopyPrefab(destChild, srcChild);
		dest->children.add(destChild);
	}
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
bool IsCommand(string str)
{
	if (str == 0) return false;
	string check = 0;
	check = strstr(str, COMMAND_TRANSLATE);
	if (check != 0) return true;
	check = 0;
	check = strstr(str, COMMAND_ROTATE);
	if (check != 0) return true;
	check = 0;
	check = strstr(str, COMMAND_SCALE);
	if (check != 0)
	if (check != 0) return true;
	check = 0;
	check = strstr(str, COMMAND_STATIC);
	if (check != 0)
	if (check != 0) return true;
	check = 0;
	check = strstr(str, COMMAND_OVERLAY);
	if (check != 0)
	if (check != 0) return true;
	check = 0;
	check = strstr(str, COMMAND_SPECULAR);
	if (check != 0)
	if (check != 0) return true;
	check = 0;
	check = strstr(str, COMMAND_UVREPEAT);
	if (check != 0)
	if (check != 0) return true;
	check = 0;
	check = strstr(str, COMMAND_UVOFFSET);
	if (check != 0)
	if (check != 0) return true;
	check = 0;
	check = strstr(str, COMMAND_CASTER);
	if (check != 0)
	if (check != 0) return true;
	check = 0;
	check = strstr(str, COMMAND_CAMERANODE);
	if (check != 0)
	if (check != 0) return true;
	check = 0;
	check = strstr(str, COMMAND_LIGHTNODE);
	if (check != 0)
	if (check != 0) return true;
	check = 0;
	check = strstr(str, COMMAND_CONTROLNODE);
	if (check != 0)
	if (check != 0) return true;
	return false;
}
bool ParseLine(string str, Scene* scene)
{
	if (str == 0 || scene == 0) return false;
	string check = 0;
	static Prefab* currentPrefab = 0;
	static bool insidePrefab = false;
	static bool addToChild = false;
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
		currentPrefab = CreatePrefab(check);
		scene->prefabs.add(currentPrefab);
		return true;
	}
	check = 0;
	check = strchr(str, '{');
	if (check != 0)
	{
		if (currentPrefab == 0) return false;
		if (insidePrefab) return false;
		insidePrefab = true;
		addToChild = false;
		return true;
	}
	check = 0;
	check = strchr(str, '}');
	if (check != 0)
	{
		if (currentPrefab == 0) return false;
		if (!insidePrefab) return false;
		insidePrefab = false;
		addToChild = false;
		currentPrefab = 0;
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_LOAD);
	if (check != 0)
	{
		if (insidePrefab) return false;
		check += strlen(COMMAND_LOAD) + 1;
		currentPrefab = CreatePrefab(0);
		Prefab* original = GetPrefab(check, scene->prefabs);
		if (original != 0)
		{
			CopyPrefab(currentPrefab, original);
		}
		scene->loadOrder.add(currentPrefab);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_PARENT);
	if (check != 0)
	{
		if (currentPrefab == 0) return false;
		if (!insidePrefab) return false;
		check += strlen(COMMAND_PARENT) + 1;
		Prefab* original = GetPrefab(check, scene->prefabs);
		Prefab* child = CreatePrefab(0);
		CopyPrefab(child, original);
		currentPrefab->children.add(child);
		addToChild = true;
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_VERTEXMAP);
	if (check != 0)
	{
		if (currentPrefab == 0) return false;
		check += strlen(COMMAND_VERTEXMAP) + 1;
		ParseFilepath(check, &currentPrefab->data.mesh);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_DIFFUSE);
	if (check != 0)
	{
		if (currentPrefab == 0) return false;
		check += strlen(COMMAND_DIFFUSE) + 1;
		ParseFilepath(check, &currentPrefab->data.diffuse);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_NORMAL);
	if (check != 0)
	{
		if (currentPrefab == 0) return false;
		check += strlen(COMMAND_NORMAL) + 1;
		ParseFilepath(check, &currentPrefab->data.normal);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_SPECULAR);
	if (check != 0)
	{
		if (currentPrefab == 0) return false;
		check += strlen(COMMAND_SPECULAR) + 1;
		ParseFilepath(check, &currentPrefab->data.specular);
		return true;
	}
	if (IsCommand(str))
	{
		if (currentPrefab == 0) return false;
		if (addToChild)
		{
			if (currentPrefab->children.length() > 0)
			{
				Prefab* child = currentPrefab->children[currentPrefab->children.length() - 1];
				child->commands.add(str);
			}
		}
		else currentPrefab->commands.add(str);
		return true;
	}
	return true;
}

bool ParseMesh(string filepath, uint* outMesh)
{
	if (filepath == 0 || outMesh == 0) return false;
	FILETYPE type = GetFiletype(filepath);
	if      (type == FILETYPE_OBJ) RegisterOBJ(outMesh, filepath);
	else if (type == FILETYPE_VMP) RegisterVMP(outMesh, filepath);
	else
	{
		return false;
	}
	return true;
}
bool ParseTexture(string filepath, uint* outTex)
{
	if (filepath == 0 || outTex == 0) return false;
	FILETYPE type = GetFiletype(filepath);
	if      (type == FILETYPE_BMP) RegisterBMP(outTex, filepath);
	else if (type == FILETYPE_TGA) RegisterTGA(outTex, filepath);
	else
	{
		return false;
	}
	return true;
}
bool ParseCameraCommand(string str)
{
	return false;
}
bool ParseLightCommand(string str)
{
	return false;
}
bool ParseControllerCommand(string str)
{
	return false;
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
	check = strstr(str, COMMAND_CAMERANODE);
	if (check != 0)
	{
		check += strlen(COMMAND_CAMERANODE) + 1;
		return ParseCameraCommand(check);
	}
	check = strstr(str, COMMAND_LIGHTNODE);
	if (check != 0)
	{
		check += strlen(COMMAND_LIGHTNODE) + 1;
		return ParseLightCommand(check);
	}
	check = strstr(str, COMMAND_CONTROLNODE);
	if (check != 0)
	{
		check += strlen(COMMAND_CONTROLNODE) + 1;
		return ParseControllerCommand(check);
	}
	return false;
}

bool BuildPrefab(Prefab* prefab, uint* outEntity)
{
	if (prefab == 0) return false;
	
	uint entity = 0;
	GenEntities(1, &entity);
	BindEntity(entity);
	
	AddShape(0);
	AddMaterial(0, 0, 0);
	BindEntity(0);

	for (uint i = 0; i < prefab->commands.length(); i++)
	{
		string command = prefab->commands[i];

		if (!ParseCommand(command)) return false;
	}
	for (uint i = 0; i < prefab->children.length(); i++)
	{
		Prefab* child = prefab->children[i];
		uint childEntity = 0;

		if (!BuildPrefab(child, &childEntity)) return false;

		ParentEntity(entity, childEntity);
	}

	if (outEntity != 0) *outEntity = entity;
	return true;
}
bool BuildScene(Scene* scene)
{
	if (scene == 0) return false;
	
	for (uint i = 0; i < scene->loadOrder.length(); i++)
	{
		Prefab* prefab = scene->loadOrder[i];

		if (!BuildPrefab(prefab, 0)) return false;
	}

	return true;
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

	LogScene(scene);

	BuildScene(scene);

	if (foundError) MALib::LOG_Out1i("FAILED TO LOAD SCENE, ERROR ON LINE :", count + 1);
	return !foundError;
}

HEX_END
#endif