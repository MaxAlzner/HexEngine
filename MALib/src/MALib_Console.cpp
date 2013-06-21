
#include "..\include\MALib.h"

int main()
{
	MALib::LOG_Initialize();
	MALib::RANDOM_Initialize();

	MALib::OBJ_MESH* mesh = 0;
	MALib::ImportOBJFile("puzzle.obj", &mesh);
	float* bake = 0;
	unsigned count = 0;
	MALib::BakeOBJ(mesh, &bake, &count);

	MALib::LOG_Unitialize();
	return 0;
}