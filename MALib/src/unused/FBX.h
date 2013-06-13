#ifndef __FBX_H_
#define __FBX_H_

class FBX
{
public:

	static void Initialize();
	static void Uninitialize();

	static void Import(const char* filepath, MESHDATA** outMesh);
	static MESHDATA* Import(const char* filepath);
	static void Import(void* data, int size, MESHDATA** outMesh);
	static MESHDATA* Import(void* data, int size);

	static void Extract(FbxMesh* mesh, MESHDATA** outMesh);
	
#if 0
	static void ExtractVertices(FbxMesh* mesh, MESHDATA** outMesh);
	static void ExtractIndices(FbxMesh* mesh, MESHDATA** outMesh);
	static void ExtractUVs(FbxMesh* mesh, MESHDATA** outMesh);
	static void ExtractNormals(FbxMesh* mesh, MESHDATA** outMesh);
	static void ExtractTangents(FbxMesh* mesh, MESHDATA** outMesh);
	static void ExtractBinormals(FbxMesh* mesh, MESHDATA** outMesh);
#endif

	static FbxManager* SDKMANAGER;
};

#endif