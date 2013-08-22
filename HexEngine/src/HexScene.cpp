#include "..\include\HexMain.h"

#ifdef _HEX_SCENE_H_
HEX_BEGIN

#define COMMAND_COMMENT "//"

#define COMMAND_TRANSLATE "translate"
#define COMMAND_ROTATE "rotate"
#define COMMAND_SCALE "scale"
#define COMMAND_STATIC "static"
#define COMMAND_OVERLAY "overlay"
#define COMMAND_SPECULAR "specular"
#define COMMAND_UVREPEAT "uvrepeat"
#define COMMAND_UVOFFSET "uvoffset"
#define COMMAND_CASTER "caster"

#define COMMAND_PARAMETER_VECTOR_X "-x"
#define COMMAND_PARAMETER_VECTOR_Y "-y"
#define COMMAND_PARAMETER_VECTOR_Z "-z"
#define COMMAND_PARAMETER_VECTOR_R "-r"
#define COMMAND_PARAMETER_VECTOR_G "-g"
#define COMMAND_PARAMETER_VECTOR_B "-b"
#define COMMAND_PARAMETER_VECTOR_U "-u"
#define COMMAND_PARAMETER_VECTOR_V "-v"

#define COMMAND_CAMERANODE "camera"
#define COMMAND_LIGHTNODE "light"
#define COMMAND_CONTROLNODE "controller"
#define COMMAND_SKYBOXNODE "skybox"

#define COMMAND_PARAMETER_LIGHTMODE_DIRECTIONAL "directional"
#define COMMAND_PARAMETER_LIGHTMODE_POINT "point"
#define COMMAND_PARAMETER_LIGHT_INTENSITY "-intensity"
#define COMMAND_PARAMETER_LIGHT_COLOR "-color"
#define COMMAND_PARAMETER_LIGHT_FALLOFF "-falloff"
#define COMMAND_PARAMETER_CONTROLLERTYPE_FIRSTPERSON "firstperson"
#define COMMAND_PARAMETER_CONTROLLERTYPE_THIRDPERSON "thirdperson"
#define COMMAND_PARAMETER_CONTROLLERTYPE_TURNTABLE "turntable"
#define COMMAND_PARAMETER_CONTROLLER_SENSITIVITY "-sensitivity"
#define COMMAND_PARAMETER_CONTROLLER_MOVESPEED "-moveSpeed"
	
#define COMMAND_MESH "mesh"
#define COMMAND_DIFFUSE "diffuse"
#define COMMAND_NORMAL "normal"
#define COMMAND_SPECULAR "specular"
	
#define COMMAND_UNITSIZE "UNIT_SIZE"
#define COMMAND_CREATEPREFAB "prefab"
#define COMMAND_PARENT "parent"
#define COMMAND_LOAD "load"

float UnitSize = 1.0f;
	
typedef struct Prefab
{
	Prefab()
	{
		memset(this, 0, sizeof(Prefab));
	}
	~Prefab()
	{
		for (uint i = 0; i < this->children.length(); i++) delete this->children[i];
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
	} filepaths;
	struct
	{
		uint mesh;
		uint diffuse;
		uint normal;
		uint specular;
	} data;
	MALib::ARRAY<Prefab*> children;
	MALib::ARRAY<string> commands;
} Prefab;
typedef struct Scene
{
	Scene()
	{
		memset(this, 0, sizeof(Scene));
	}
	~Scene()
	{
		for (uint i = 0; i < this->prefabs.length(); i++) delete this->prefabs[i];
		for (uint i = 0; i < this->loadOrder.length(); i++) delete this->loadOrder[i];
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
	MALib::LOG_Message("VERTEX MAP", prefab->filepaths.mesh);
	MALib::LOG_Message("DIFFUSE", prefab->filepaths.diffuse);
	MALib::LOG_Message("NORMAL", prefab->filepaths.normal);
	MALib::LOG_Message("SPECULAR", prefab->filepaths.specular);
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

	scene->unitSize = 1.0f;
	scene->prefabs.resize(32);
	scene->loadOrder.resize(64);
	scene->file = file;

	return scene;
}
Prefab* CreatePrefab(string name)
{
	Prefab* prefab = new Prefab;

	prefab->name = name;
	prefab->commands.resize(8);
	prefab->children.resize(8);

	return prefab;
}
void DestroyScene(Scene** scene)
{
	if (scene == 0) return;
	delete *scene;
	*scene = 0;
}
void DestroyPrefab(Prefab** prefab)
{
	if (prefab == 0) return;
	delete *prefab;
	*prefab = 0;
}
void CopyPrefab(Prefab* dest, Prefab* src)
{
	if (dest == 0 || src == 0) return;

	dest->name = src->name;
	dest->filepaths.mesh = src->filepaths.mesh;
	dest->filepaths.diffuse = src->filepaths.diffuse;
	dest->filepaths.normal = src->filepaths.normal;
	dest->filepaths.specular = src->filepaths.specular;
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

void RemoveWhitespace(string* str)
{
	while (true)
	{
		char ch = (*str)[0];
		if (ch == '\n') return;
		if (ch == '\0') return;
		if (ch >= '!' && ch <= '~') return;
		*str += 1;
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
bool ParseVector(string str, float* v0, float* v1, float* v2)
{
	return sscanf(str, "%f %f %f", v0, v1, v2) == 3;
}
bool ParseVector(string str, float* v0, float* v1)
{
	return sscanf(str, "%f %f", v0, v1) == 2;
}
bool ParseValue(string str, float* v0)
{
	return sscanf(str, "%f", v0) == 1;
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
	check = strstr(str, COMMAND_SKYBOXNODE);
	if (check != 0)
	if (check != 0) return true;
	return false;
}
bool ParseLine(string str, Scene* scene)
{
	if (str == 0 || scene == 0) return false;
	RemoveWhitespace(&str);
	string check = 0;
	static Prefab* currentPrefab = 0;
	static bool insidePrefab = false;
	static bool addToChild = false;
	check = strstr(str, COMMAND_COMMENT);
	if (check != 0)
	{
		return true;
	}
	check = strstr(str, COMMAND_UNITSIZE);
	if (check != 0)
	{
		check += strlen(COMMAND_UNITSIZE) + 1;
		sscanf(check, "%f", &scene->unitSize);
		UnitSize = scene->unitSize;
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
	check = strstr(str, COMMAND_MESH);
	if (check != 0)
	{
		if (currentPrefab == 0) return false;
		check += strlen(COMMAND_MESH) + 1;
		if (addToChild)
		{
			if (currentPrefab->children.length() > 0)
			{
				Prefab* child = currentPrefab->children[currentPrefab->children.length() - 1];
				ParseFilepath(check, &child->filepaths.mesh);
			}
		}
		else 
			ParseFilepath(check, &currentPrefab->filepaths.mesh);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_DIFFUSE);
	if (check != 0)
	{
		if (currentPrefab == 0) return false;
		check += strlen(COMMAND_DIFFUSE) + 1;
		if (addToChild)
		{
			if (currentPrefab->children.length() > 0)
			{
				Prefab* child = currentPrefab->children[currentPrefab->children.length() - 1];
				ParseFilepath(check, &child->filepaths.diffuse);
			}
		}
		else 
			ParseFilepath(check, &currentPrefab->filepaths.diffuse);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_NORMAL);
	if (check != 0)
	{
		if (currentPrefab == 0) return false;
		check += strlen(COMMAND_NORMAL) + 1;
		if (addToChild)
		{
			if (currentPrefab->children.length() > 0)
			{
				Prefab* child = currentPrefab->children[currentPrefab->children.length() - 1];
				ParseFilepath(check, &child->filepaths.normal);
			}
		}
		else 
			ParseFilepath(check, &currentPrefab->filepaths.normal);
		return true;
	}
	check = 0;
	check = strstr(str, COMMAND_SPECULAR);
	if (check != 0)
	{
		if (currentPrefab == 0) return false;
		check += strlen(COMMAND_SPECULAR) + 1;
		if (addToChild)
		{
			if (currentPrefab->children.length() > 0)
			{
				Prefab* child = currentPrefab->children[currentPrefab->children.length() - 1];
				ParseFilepath(check, &child->filepaths.specular);
			}
		}
		else 
			ParseFilepath(check, &currentPrefab->filepaths.specular);
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
	if (str == 0 || BoundEntity == 0) return false;

	float fovAngle = 0.0f;
	float nearZ = 0.0f;
	float farZ = 0.0f;
	if (!ParseVector(str, &fovAngle, &nearZ, &farZ)) return false;
	AddCamera(fovAngle, nearZ * UnitSize, farZ * UnitSize);

	return true;
}
bool ParseLightCommand(string str)
{
	if (str == 0 || BoundEntity == 0) return false;

	static char type[256];
	memset(type, 0, sizeof(char) * 256);
	sscanf(str, "%s", type);

	if (strcmp(type, COMMAND_PARAMETER_LIGHTMODE_DIRECTIONAL) == 0)
	{
		str += strlen(COMMAND_PARAMETER_LIGHTMODE_DIRECTIONAL) + 1;

		float intensity = 1.0f;
		if (!ParseValue(str, &intensity)) return false;
		AddDirectionalLight(intensity);
	}
	else if (strcmp(type, COMMAND_PARAMETER_LIGHTMODE_POINT) == 0)
	{
		str += strlen(COMMAND_PARAMETER_LIGHTMODE_POINT) + 1;

		float intensity = 1.0f;
		if (!ParseValue(str, &intensity)) return false;
		AddPointLight(intensity);
	}
	else if (strcmp(type, COMMAND_PARAMETER_LIGHT_INTENSITY) == 0)
	{
		str += strlen(COMMAND_PARAMETER_LIGHT_INTENSITY) + 1;
		
		float intensity = 1.0f;
		if (!ParseValue(str, &intensity)) return false;
		ChangeParameter(HEX::PARAMETER_LIGHT_INTENSITY, intensity);
	}
	else if (strcmp(type, COMMAND_PARAMETER_LIGHT_COLOR) == 0)
	{
		str += strlen(COMMAND_PARAMETER_LIGHT_COLOR) + 1;

		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		if (!ParseVector(str, &r, &g, &b)) return false;
		ChangeParameter(HEX::PARAMETER_LIGHT_COLOR_RGB, r, g, b);
	}
	else if (strcmp(type, COMMAND_PARAMETER_LIGHT_FALLOFF) == 0)
	{
		str += strlen(COMMAND_PARAMETER_LIGHT_FALLOFF) + 1;

		float constant = 0.0f;
		float linear = 0.0f;
		float quad = 0.0f;
		if (!ParseVector(str, &constant, &linear, &quad)) return false;
		ChangeParameter(HEX::PARAMETER_LIGHT_FALLOFF_XYZ, constant, linear, quad);
	}
	else return false;

	return true;
}
bool ParseControllerCommand(string str)
{
	if (str == 0 || BoundEntity == 0) return false;

	static char type[256];
	memset(type, 0, sizeof(char) * 256);
	sscanf(str, "%s", type);
	
	if (strcmp(type, COMMAND_PARAMETER_CONTROLLERTYPE_FIRSTPERSON) == 0)
	{
		str += strlen(COMMAND_PARAMETER_CONTROLLERTYPE_FIRSTPERSON) + 1;

		float sensitivity = 0.0f;
		float moveSpeed = 0.0f;
		if (!ParseVector(str, &sensitivity, &moveSpeed)) return false;
		FirstPersonNode* controller = AddComponent<FirstPersonNode>();
		controller->sensitivity.x = sensitivity;
		controller->sensitivity.y = sensitivity;
		controller->moveSpeed.x = moveSpeed;
		controller->moveSpeed.y = moveSpeed;
	}
	else if (strcmp(type, COMMAND_PARAMETER_CONTROLLERTYPE_THIRDPERSON) == 0)
	{
		str += strlen(COMMAND_PARAMETER_CONTROLLERTYPE_THIRDPERSON) + 1;
		
		float sensitivity = 0.0f;
		float moveSpeed = 0.0f;
		if (!ParseVector(str, &sensitivity, &moveSpeed)) return false;
		ThirdPersonNode* controller = AddComponent<ThirdPersonNode>();
		controller->sensitivity.x = sensitivity;
		controller->sensitivity.y = sensitivity;
		controller->moveSpeed.x = moveSpeed;
		controller->moveSpeed.y = moveSpeed;
	}
	else if (strcmp(type, COMMAND_PARAMETER_CONTROLLERTYPE_TURNTABLE) == 0)
	{
		str += strlen(COMMAND_PARAMETER_CONTROLLERTYPE_TURNTABLE) + 1;
		
		float turnSpeed = 0.0f;
		if (!ParseValue(str, &turnSpeed)) return false;
		TurnTableNode* controller = AddComponent<TurnTableNode>();
		controller->turnSpeed = turnSpeed;
	}

	return true;
}
bool ParseSkyboxCommand(string str)
{
	if (str == 0 || BoundEntity == 0) return false;
	
	SkyboxNode* skybox = AddComponent<SkyboxNode>();

	return true;
}
bool ParseTransformation(string str, float* x, float* y, float* z)
{
	if (str == 0 || x == 0 || y == 0 || z == 0 || BoundEntity == 0) return false;
	
	if (ParseVector(str, x, y, z)) return true;

	static char type[256];
	memset(type, 0, sizeof(char) * 256);
	sscanf(str, "%s", type);

	if (strcmp(type, COMMAND_PARAMETER_VECTOR_X) == 0)
	{
		str += strlen(COMMAND_PARAMETER_VECTOR_X) + 1;

		if (!ParseValue(str, x)) return false;
	}
	else if (strcmp(type, COMMAND_PARAMETER_VECTOR_Y) == 0)
	{
		str += strlen(COMMAND_PARAMETER_VECTOR_Y) + 1;

		if (!ParseValue(str, y)) return false;
	}
	else if (strcmp(type, COMMAND_PARAMETER_VECTOR_Z) == 0)
	{
		str += strlen(COMMAND_PARAMETER_VECTOR_Z) + 1;

		if (!ParseValue(str, z)) return false;
	}
	else return false;

	return true;
}
bool ParseColor(string str, float* r, float* g, float* b)
{
	if (str == 0 || r == 0 || g == 0 || b == 0 || BoundEntity == 0) return false;
	
	if (ParseVector(str, r, g, b)) return true;

	static char type[256];
	memset(type, 0, sizeof(char) * 256);
	sscanf(str, "%s", type);

	if (strcmp(type, COMMAND_PARAMETER_VECTOR_R) == 0)
	{
		str += strlen(COMMAND_PARAMETER_VECTOR_R) + 1;

		if (!ParseValue(str, r)) return false;
	}
	else if (strcmp(type, COMMAND_PARAMETER_VECTOR_G) == 0)
	{
		str += strlen(COMMAND_PARAMETER_VECTOR_G) + 1;

		if (!ParseValue(str, g)) return false;
	}
	else if (strcmp(type, COMMAND_PARAMETER_VECTOR_B) == 0)
	{
		str += strlen(COMMAND_PARAMETER_VECTOR_B) + 1;

		if (!ParseValue(str, b)) return false;
	}
	else return false;
	
	return true;
}
bool ParseTexcoord(string str, float* u, float* v)
{
	if (str == 0 || u == 0 || v == 0 || BoundEntity == 0) return false;
	
	if (ParseVector(str, u, v)) return true;

	static char type[256];
	memset(type, 0, sizeof(char) * 256);
	sscanf(str, "%s", type);

	if (strcmp(type, COMMAND_PARAMETER_VECTOR_U) == 0)
	{
		str += strlen(COMMAND_PARAMETER_VECTOR_U) + 1;

		if (!ParseValue(str, u)) return false;
	}
	else if (strcmp(type, COMMAND_PARAMETER_VECTOR_V) == 0)
	{
		str += strlen(COMMAND_PARAMETER_VECTOR_V) + 1;

		if (!ParseValue(str, v)) return false;
	}
	else return false;
	
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
		if (!ParseTransformation(check, &x, &y, &z)) return false;
		BoundEntity->transform->translate(x * UnitSize, y * UnitSize, z * UnitSize);
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
		if (!ParseTransformation(check, &x, &y, &z)) return false;
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
		if (!ParseTransformation(check, &x, &y, &z)) return false;
		BoundEntity->transform->scale(x * UnitSize, y * UnitSize, z * UnitSize);
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
		if (!ParseColor(check, &x, &y, &z)) return false;
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
		if (!ParseColor(check, &x, &y, &z)) return false;
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
		if (!ParseTexcoord(check, &u, &v)) return false;
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
		if (!ParseTexcoord(check, &u, &v)) return false;
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
	check = strstr(str, COMMAND_SKYBOXNODE);
	if (check != 0)
	{
		check += strlen(COMMAND_SKYBOXNODE) + 1;
		return ParseSkyboxCommand(check);
	}
	return false;
}

bool BuildPrefab(Prefab* prefab, uint* outEntity)
{
	if (prefab == 0) return false;
	
	uint entity = 0;
	GenEntities(1, &entity);
	BindEntity(entity);

	ParseMesh(prefab->filepaths.mesh, &prefab->data.mesh);
	ParseTexture(prefab->filepaths.diffuse, &prefab->data.diffuse);
	ParseTexture(prefab->filepaths.normal, &prefab->data.normal);
	ParseTexture(prefab->filepaths.specular, &prefab->data.specular);
	
	AddShape(prefab->data.mesh);
	AddMaterial(prefab->data.diffuse, prefab->data.normal, prefab->data.specular);
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

HEX_API Scene* LoadScene(const string filepath)
{
	if (filepath == 0) return 0;

	Scene* scene = CreateScene(filepath);
	if (scene == 0) return 0;

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

	if (foundError) MALib::LOG_Out1i("FAILED TO LOAD SCENE, ERROR ON LINE :", count + 1);
	return scene;
}

HEX_END
#endif