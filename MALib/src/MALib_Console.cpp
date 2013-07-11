
#include "..\include\MALib.h"

int main()
{
	MALib::LOG_Initialize(true);
	MALib::RANDOM_Initialize();

	/*MALib::LOG_Message("IMPORTING OBJ");
	MALib::OBJ_MESH* mesh = 0;
	MALib::ImportOBJFile("puzzle.obj", &mesh);

	MALib::LOG_Message("BAKING OBJ");
	MALib::VERTEXBUFFER* bake = 0;
	MALib::BakeOBJ(mesh, &bake);
	
	MALib::LOG_Message("IMPORTING TGA");
	MALib::SURFACE* tgaTest = 0;
	MALib::ImportTGAFile("uv_layout.tga", &tgaTest);
	
	MALib::LOG_Message("IMPORTING BMP");
	MALib::SURFACE* bmpTest = 0;
	MALib::ImportBMPFile("uv_layout.bmp", &bmpTest);
	
	MALib::LOG_Message("EXPORTING VMP");
	MALib::ExportVMPFile("puzzle.vmp", bake);
	
	MALib::LOG_Message("IMPORTING VMP");
	MALib::VERTEXBUFFER* vmpTest = 0;
	MALib::ImportVMPFile("puzzle.vmp", &vmpTest);
	
	MALib::LOG_Message("FREEING OBJ AND BAKE");
	MALib::FreeOBJMesh(&mesh);
	MALib::FreeVertexBuffer(&bake);*/

	MALib::TEXTFILE* shaderFile = 0;
	MALib::ImportTextFile("gl_shader.frag", &shaderFile);
	MALib::FreeTextFile(&shaderFile);

	MALib::LOG_Unitialize();
	return 0;
}