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
	uint a_vertex;
	uint a_texcoord;
	uint a_normal;
	uint b_vertex;
	uint b_texcoord;
	uint b_normal;
	uint c_vertex;
	uint c_texcoord;
	uint c_normal;
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

bool MALIB_API ImportOBJFile(const string filepath, OBJ_MESH** outMesh);

bool MALIB_API BakeOBJ(OBJ_MESH* mesh, VERTEXBUFFER** outBake);

void MALIB_API FreeOBJMesh(OBJ_MESH** mesh);

_MALIB_END
#endif