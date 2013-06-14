#ifndef _MA_OBJ_H_
#define _MA_OBJ_H_

#ifndef _INC_STDIO
#include <stdio.h>
#endif
#ifndef _MA_ARRAY_H_
#include "MA_Array.h"
#endif

struct MALIB_API OBJ_VERTEX
{
	float x, y, z, w;
};
struct MALIB_API OBJ_UVCOORD
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
	unsigned int a_uvcoord;
	unsigned int a_normal;
	unsigned int b_vertex;
	unsigned int b_uvcoord;
	unsigned int b_normal;
	unsigned int c_vertex;
	unsigned int c_uvcoord;
	unsigned int c_normal;
};
struct MALIB_API OBJ_MESH
{
	ARRAY<OBJ_VERTEX> vertices;
	ARRAY<OBJ_UVCOORD> uvcoords;
	ARRAY<OBJ_NORMAL> normals;
	ARRAY<OBJ_FACE> faces;
};

void MALIB_API ImportOBJFile(const char* filepath, OBJ_MESH** outMesh);

#endif