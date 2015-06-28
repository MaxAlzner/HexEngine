#include "..\include\MALib.h"

#ifdef _MA_OBJ_H_
_MALIB_BEGIN
	
MALIB_API OBJ_MESH::OBJ_MESH()
{
}
MALIB_API OBJ_MESH::~OBJ_MESH()
{
	this->vertices.clear();
	this->texcoords.clear();
	this->normals.clear();
	this->tangents.clear();
	this->binormals.clear();
	this->faces.clear();
}

bool MALIB_API ImportOBJFile(const string filepath, OBJ_MESH** outMesh)
{
	if (filepath == NULL || outMesh == NULL) return false;

	uint vertices = 0;
	uint texcoords = 0;
	uint normals = 0;
	uint faces = 0;

	TEXTFILE* file = 0;
	if (!ImportTextFile(filepath, &file)) 
		return false;
	if (file == NULL) 
		return false;

	for (unsigned i = 0; i < file->lines.length(); i++)
	{
		string line = file->lines[i];
		if (line == 0) continue;
		char first = line[0];
		if (first == '\0') continue;
		if (first == 'v')
		{
			char second = line[1];
			if (second == '\0') continue;
			if (second == 'n') normals++;
			else if (second == 't') texcoords++;
			else vertices++;
		}
		else if (first == 'f') 
			faces++;
	}
	OBJ_MESH* mesh = new OBJ_MESH;
	mesh->vertices.resize(vertices);
	mesh->texcoords.resize(texcoords);
	mesh->normals.resize(normals);
	mesh->tangents.resize(normals);
	mesh->binormals.resize(normals);
	mesh->faces.resize(faces);

	for (uint i = 0; i < file->lines.length(); i++)
	{
		char* line = file->lines[i];
		if (line == 0) continue;
		char first = line[0];
		if (first == '\0') continue;

		if (first == 'v')
		{
			char second = line[1];
			if (second == '\0') continue;
			if (second == 'n')
			{
				OBJ_NORMAL normal;
				sscanf_s(line, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
				mesh->normals.add(normal);
			}
			else if (second == 't')
			{
				OBJ_TEXCOORD tex;
				sscanf_s(line, "vt %f %f", &tex.u, &tex.v);
				mesh->texcoords.add(tex);
			}
			else
			{
				OBJ_VERTEX vert;
				sscanf_s(line, "v %f %f %f", &vert.x, &vert.y, &vert.z);
				mesh->vertices.add(vert);
			}
		}
		else if (first == 'f')
		{
			OBJ_FACE face;
			sscanf_s(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &face.a_vertex, &face.a_texcoord, &face.a_normal, &face.b_vertex, &face.b_texcoord, &face.b_normal, &face.c_vertex, &face.c_texcoord, &face.c_normal);
			face.a_vertex--;
			face.b_vertex--;
			face.c_vertex--;
			face.a_texcoord--;
			face.b_texcoord--;
			face.c_texcoord--;
			face.a_normal--;
			face.b_normal--;
			face.c_normal--;
			mesh->faces.add(face);
		}
	}

#if 0
	ARRAY<VEC3> faceTangents(faces);
	ARRAY<VEC3> faceBinormals(faces);
	for (uint i = 0; i < faces; i++)
	{
		OBJ_FACE face = mesh->faces[i];
		OBJ_VERTEX a = mesh->vertices[face.a_vertex];
		OBJ_VERTEX b = mesh->vertices[face.b_vertex];
		OBJ_VERTEX c = mesh->vertices[face.c_vertex];
		OBJ_TEXCOORD at = mesh->texcoords[face.a_texcoord];
		OBJ_TEXCOORD bt = mesh->texcoords[face.b_texcoord];
		OBJ_TEXCOORD ct = mesh->texcoords[face.c_texcoord];
		
		VEC3 tangent, binormal;
		CalculateTangent(
			VEC3(a.x, a.y, a.z), VEC3(b.x, b.y, b.z), VEC3(c.x, c.y, c.z), 
			VEC2(at.u, at.v), VEC2(bt.u, bt.v), VEC2(ct.u, ct.v), 
			&tangent, &binormal);
		faceTangents.add(tangent);
		faceBinormals.add(binormal);
	}
	for (uint i = 0; i < normals; i++)
	{
		VEC3 tangentSum(0.0f);
		VEC3 binormalSum(0.0f);
		float shared = 0.0f;
		for (uint k = 0; k < faces; k++)
		{
			OBJ_FACE face = mesh->faces[k];
			if (face.a_normal == i || face.b_normal == i || face.c_normal == i)
			{
				tangentSum += faceTangents[i];
				binormalSum += faceBinormals[i];
				shared += 1.0f;
			}
			tangentSum /= shared;
			binormalSum /= shared;
		}
		tangentSum = Normalize(tangentSum);
		binormalSum = Normalize(binormalSum);
		OBJ_NORMAL tangent;
		tangent.x = tangentSum.x;
		tangent.y = tangentSum.y;
		tangent.z = tangentSum.z;
		OBJ_NORMAL binormal;
		binormal.x = binormalSum.x;
		binormal.y = binormalSum.y;
		binormal.z = binormalSum.z;
		mesh->tangents.add(tangent);
		mesh->binormals.add(binormal);
	}
	faceTangents.clear();
	faceBinormals.clear();
#endif
	
	*outMesh = mesh;
	FreeTextFile(&file);
	return true;
}

bool MALIB_API BakeOBJ(OBJ_MESH* mesh, VERTEXBUFFER** outBake)
{
	if (mesh == NULL || outBake == NULL) return false;

	uint faces = mesh->faces.length();
	uint indices = faces * 3;
	uint stride = 12;
	uint offset = indices * 4;
	uint components = 5;
	uint bufferSize = faces * stride * components;
	float* buffer = new float[bufferSize];
	for (uint i = 0; i < faces; i++)
	{
		OBJ_FACE face = mesh->faces[i];
		OBJ_VERTEX a = mesh->vertices[face.a_vertex];
		OBJ_VERTEX b = mesh->vertices[face.b_vertex];
		OBJ_VERTEX c = mesh->vertices[face.c_vertex];
		OBJ_TEXCOORD at = mesh->texcoords[face.a_texcoord];
		OBJ_TEXCOORD bt = mesh->texcoords[face.b_texcoord];
		OBJ_TEXCOORD ct = mesh->texcoords[face.c_texcoord];
		OBJ_NORMAL an = mesh->normals[face.a_normal];
		OBJ_NORMAL bn = mesh->normals[face.b_normal];
		OBJ_NORMAL cn = mesh->normals[face.c_normal];

		uint vertexOffset = i * stride;
		uint texcoordOffset = (i * stride) + offset;
		uint normalOffset = (i * stride) + (offset * 2);
		uint tangentOffset = (i * stride) + (offset * 3);
		uint binormalOffset = (i * stride) + (offset * 4);

		buffer[vertexOffset     ] = a.x;
		buffer[vertexOffset +  1] = a.y;
		buffer[vertexOffset +  2] = a.z;
		buffer[vertexOffset +  3] = 1.0f;
		buffer[vertexOffset +  4] = b.x;
		buffer[vertexOffset +  5] = b.y;
		buffer[vertexOffset +  6] = b.z;
		buffer[vertexOffset +  7] = 1.0f;
		buffer[vertexOffset +  8] = c.x;
		buffer[vertexOffset +  9] = c.y;
		buffer[vertexOffset + 10] = c.z;
		buffer[vertexOffset + 11] = 1.0f;

		buffer[texcoordOffset     ] = at.u;
		buffer[texcoordOffset +  1] = at.v;
		buffer[texcoordOffset +  2] = 0.0f;
		buffer[texcoordOffset +  3] = 0.0f;
		buffer[texcoordOffset +  4] = bt.u;
		buffer[texcoordOffset +  5] = bt.v;
		buffer[texcoordOffset +  6] = 0.0f;
		buffer[texcoordOffset +  7] = 0.0f;
		buffer[texcoordOffset +  8] = ct.u;
		buffer[texcoordOffset +  9] = ct.v;
		buffer[texcoordOffset + 10] = 0.0f;
		buffer[texcoordOffset + 11] = 0.0f;

		buffer[normalOffset     ] = an.x;
		buffer[normalOffset +  1] = an.y;
		buffer[normalOffset +  2] = an.z;
		buffer[normalOffset +  3] = 0.0f;
		buffer[normalOffset +  4] = bn.x;
		buffer[normalOffset +  5] = bn.y;
		buffer[normalOffset +  6] = bn.z;
		buffer[normalOffset +  7] = 0.0f;
		buffer[normalOffset +  8] = cn.x;
		buffer[normalOffset +  9] = cn.y;
		buffer[normalOffset + 10] = cn.z;
		buffer[normalOffset + 11] = 0.0f;

#if 1
		VEC3 tangent, binormal;
		CalculateTangent(
			VEC3(a.x, a.y, a.z), VEC3(b.x, b.y, b.z), VEC3(c.x, c.y, c.z), 
			VEC2(at.u, at.v), VEC2(bt.u, bt.v), VEC2(ct.u, ct.v), 
			&tangent, &binormal);

		buffer[tangentOffset     ] = tangent.x;
		buffer[tangentOffset +  1] = tangent.y;
		buffer[tangentOffset +  2] = tangent.z;
		buffer[tangentOffset +  3] = 0.0f;
		buffer[tangentOffset +  4] = tangent.x;
		buffer[tangentOffset +  5] = tangent.y;
		buffer[tangentOffset +  6] = tangent.z;
		buffer[tangentOffset +  7] = 0.0f;
		buffer[tangentOffset +  8] = tangent.x;
		buffer[tangentOffset +  9] = tangent.y;
		buffer[tangentOffset + 10] = tangent.z;
		buffer[tangentOffset + 11] = 0.0f;

		buffer[binormalOffset     ] = binormal.x;
		buffer[binormalOffset +  1] = binormal.y;
		buffer[binormalOffset +  2] = binormal.z;
		buffer[binormalOffset +  3] = 0.0f;
		buffer[binormalOffset +  4] = binormal.x;
		buffer[binormalOffset +  5] = binormal.y;
		buffer[binormalOffset +  6] = binormal.z;
		buffer[binormalOffset +  7] = 0.0f;
		buffer[binormalOffset +  8] = binormal.x;
		buffer[binormalOffset +  9] = binormal.y;
		buffer[binormalOffset + 10] = binormal.z;
		buffer[binormalOffset + 11] = 0.0f;
#else
		OBJ_NORMAL atan = mesh->tangents[face.a_normal];
		OBJ_NORMAL btan = mesh->tangents[face.b_normal];
		OBJ_NORMAL ctan = mesh->tangents[face.c_normal];
		OBJ_NORMAL abi = mesh->binormals[face.a_normal];
		OBJ_NORMAL bbi = mesh->binormals[face.b_normal];
		OBJ_NORMAL cbi = mesh->binormals[face.c_normal];

		buffer[tangentOffset     ] = atan.x;
		buffer[tangentOffset +  1] = atan.y;
		buffer[tangentOffset +  2] = atan.z;
		buffer[tangentOffset +  3] = 0.0f;
		buffer[tangentOffset +  4] = btan.x;
		buffer[tangentOffset +  5] = btan.y;
		buffer[tangentOffset +  6] = btan.z;
		buffer[tangentOffset +  7] = 0.0f;
		buffer[tangentOffset +  8] = ctan.x;
		buffer[tangentOffset +  9] = ctan.y;
		buffer[tangentOffset + 10] = ctan.z;
		buffer[tangentOffset + 11] = 0.0f;

		buffer[binormalOffset     ] = abi.x;
		buffer[binormalOffset +  1] = abi.y;
		buffer[binormalOffset +  2] = abi.z;
		buffer[binormalOffset +  3] = 0.0f;
		buffer[binormalOffset +  4] = bbi.x;
		buffer[binormalOffset +  5] = bbi.y;
		buffer[binormalOffset +  6] = bbi.z;
		buffer[binormalOffset +  7] = 0.0f;
		buffer[binormalOffset +  8] = cbi.x;
		buffer[binormalOffset +  9] = cbi.y;
		buffer[binormalOffset + 10] = cbi.z;
		buffer[binormalOffset + 11] = 0.0f;
#endif
	}

	*outBake = CreateVertexBuffer((void*)buffer, bufferSize, 4 * sizeof(float), indices);

	return true;
}

void MALIB_API FreeOBJMesh(OBJ_MESH** mesh)
{
	delete *mesh;
	*mesh = 0;
}

_MALIB_END
#endif