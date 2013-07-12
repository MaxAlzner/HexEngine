#ifndef _MA_OBJ_H_
#define _MA_OBJ_H_
_MALIB_BEGIN

#ifndef _MA_FILE_H_
#include "MA_File.h"
#endif
#ifndef _MA_ARRAY_H_
#include "MA_Array.h"
#endif
#ifndef _MA_VERTEXBUFFER_H_
#include "MA_VertexBuffer.h"
#endif

struct MALIB_API OBJ_VERTEX
{
	float x, y, z;
};
struct MALIB_API OBJ_TEXCOORD
{
	float u, v;
};
struct MALIB_API OBJ_NORMAL
{
	float x, y, z;
};
struct MALIB_API OBJ_FACE
{
	unsigned int a_vertex;
	unsigned int a_texcoord;
	unsigned int a_normal;
	unsigned int b_vertex;
	unsigned int b_texcoord;
	unsigned int b_normal;
	unsigned int c_vertex;
	unsigned int c_texcoord;
	unsigned int c_normal;
};
struct MALIB_API OBJ_MESH
{
	OBJ_MESH();
	~OBJ_MESH();

	ARRAY<OBJ_VERTEX> vertices;
	ARRAY<OBJ_TEXCOORD> texcoords;
	ARRAY<OBJ_NORMAL> normals;
	ARRAY<OBJ_NORMAL> tangents;
	ARRAY<OBJ_NORMAL> binormals;
	ARRAY<OBJ_FACE> faces;
};

bool MALIB_API ImportOBJFile(const char* filepath, OBJ_MESH** outMesh);

bool MALIB_API BakeOBJ(OBJ_MESH* mesh, VERTEXBUFFER** outBake);

void MALIB_API FreeOBJMesh(OBJ_MESH** mesh);

_MALIB_END
#endif