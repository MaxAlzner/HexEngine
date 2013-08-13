#include "..\include\HexMain.h"

#ifdef _HEX_SCENE_H_
HEX_BEGIN
	
typedef struct Prefab
{
	~Prefab()
	{
		if (this->name != 0) delete [] name;
	}
	string name;
	uint mesh;
	uint diffuse;
	uint normal;
	uint specular;
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;
	bool isStatic;
	MALib::ARRAY<Prefab*> children;
} Prefab;

//MALib::ARRAY<uint> MeshSlots;
//MALib::ARRAY<uint> TextureSlots;
//MALib::ARRAY<Prefab*> Prefabs;

string ParseFilepath(string line, string buffer)
{
	if (line == 0 || buffer == 0) return 0;
	
	strcpy(buffer, line);
	char* filepath = strchr(buffer, '\"') + 1;
	size_t span = strcspn(filepath, "\"");
	if (span < 1) return 0;
	filepath[span] = '\0';

	return filepath;
}
bool ParseBoolean(string str)
{
	if (strcmp(str, "true") == 0) return true;
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
	MALib::ARRAY<Prefab*> Prefabs;
	/*MeshSlots.clear();
	MeshSlots.resize(64);
	TextureSlots.clear();
	TextureSlots.resize(256);
	Prefabs.clear();*/
	Prefabs.resize(64);
	
	float unitSize = 1.0f;

	bool foundError = false;
	char* scratch = new char[256];
	bool foundPrefab = false;
	bool enteredPrefab = false;
	Prefab* currentPrefab = 0;
	for (uint i = 0; i < file->lines.length(); i++)
	{
		memset(scratch, 0, sizeof(char) * 256);
		string line = file->lines[i];

		if (strlen(line) < 1) continue;
		sscanf(line, "%s", scratch);

		if (strcmp(scratch, "UNIT_SIZE") == 0)
		{
			sscanf(line, "UNIT_SIZE %f", &unitSize);
		}
		else if (strcmp(scratch, "prefab") == 0)
		{
			foundPrefab = true;
			currentPrefab = new Prefab;
			memset(currentPrefab, 0, sizeof(Prefab));
			char* name = new char[64];
			memset(name, 0, sizeof(char) * 64);
			sscanf(line, "prefab %s", name);
			currentPrefab->name = name;
			Prefabs.add(currentPrefab);
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
		else if (strcmp(scratch, "vertexMap") == 0)
		{
			if (currentPrefab == 0)
			{
				foundError = true;
				break;
			}
			memset(scratch, 0, sizeof(char) * 256);
			string filepath = ParseFilepath(line, scratch);
			if (filepath == 0 || GetFiletype(filepath) != FILETYPE_VMP)
			{
				foundError = true;
				break;
			}
			uint mesh = 0;
			RegisterVMP(&mesh, filepath);
			currentPrefab->mesh = mesh;
		}
		else if (strcmp(scratch, "diffuse") == 0)
		{
			if (currentPrefab == 0)
			{
				foundError = true;
				break;
			}
			memset(scratch, 0, sizeof(char) * 256);
			string filepath = ParseFilepath(line, scratch);
			if (filepath == 0)
			{
				foundError = true;
				break;
			}
			uint texture = 0;
			FILETYPE type = GetFiletype(filepath);
			if      (type == FILETYPE_BMP) RegisterBMP(&texture, filepath);
			else if (type == FILETYPE_TGA) RegisterTGA(&texture, filepath);
			else
			{
				foundError = true;
				break;
			}
			currentPrefab->diffuse = texture;
		}
		else if (strcmp(scratch, "normal") == 0)
		{
			if (currentPrefab == 0)
			{
				foundError = true;
				break;
			}
			memset(scratch, 0, sizeof(char) * 256);
			string filepath = ParseFilepath(line, scratch);
			if (filepath == 0)
			{
				foundError = true;
				break;
			}
			uint texture = 0;
			FILETYPE type = GetFiletype(filepath);
			if      (type == FILETYPE_BMP) RegisterBMP(&texture, filepath);
			else if (type == FILETYPE_TGA) RegisterTGA(&texture, filepath);
			else
			{
				foundError = true;
				break;
			}
			currentPrefab->normal = texture;
		}
		else if (strcmp(scratch, "specular") == 0)
		{
			if (currentPrefab == 0)
			{
				foundError = true;
				break;
			}
			memset(scratch, 0, sizeof(char) * 256);
			string filepath = ParseFilepath(line, scratch);
			if (filepath == 0)
			{
				foundError = true;
				break;
			}
			uint texture = 0;
			FILETYPE type = GetFiletype(filepath);
			if      (type == FILETYPE_BMP) RegisterBMP(&texture, filepath);
			else if (type == FILETYPE_TGA) RegisterTGA(&texture, filepath);
			else
			{
				foundError = true;
				break;
			}
			currentPrefab->specular = texture;
		}
		else if (strcmp(scratch, "static") == 0)
		{
			char* isStatic = strstr(line, "true");
			if (isStatic != 0) currentPrefab->isStatic = true;
		}
		else if (strcmp(scratch, "translate") == 0)
		{
			float x = 0.0f;
			float y = 0.0f;
			float z = 0.0f;
			string translation = strstr(line, "translate");
			sscanf(translation, "translate %f %f %f", &x, &y, &z);
			currentPrefab->translation.x += x;
			currentPrefab->translation.y += y;
			currentPrefab->translation.z += z;
		}
		else if (strcmp(scratch, "rotate") == 0)
		{
			float x = 0.0f;
			float y = 0.0f;
			float z = 0.0f;
			string translation = strstr(line, "rotate");
			sscanf(translation, "rotate %f %f %f", &x, &y, &z);
			currentPrefab->translation.x = MALib::Module(currentPrefab->translation.x + x, 360.0f);
			currentPrefab->translation.y = MALib::Module(currentPrefab->translation.y + y, 360.0f);
			currentPrefab->translation.z = MALib::Module(currentPrefab->translation.z + z, 360.0f);
		}
		else if (strcmp(scratch, "scale") == 0)
		{
			float x = 0.0f;
			float y = 0.0f;
			float z = 0.0f;
			string translation = strstr(line, "scale");
			sscanf(translation, "scale %f %f %f", &x, &y, &z);
			currentPrefab->translation.x *= x;
			currentPrefab->translation.y *= y;
			currentPrefab->translation.z *= z;
		}
	}
	delete [] scratch;
	return !foundError;
}

HEX_END
#endif