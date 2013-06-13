#include "StdAfx.h"

void ImportOBJFile(const char* filepath, MESHDATA** outMesh)
{
	if (filepath == NULL) return;
	if (outMesh == NULL) return;

	vector<VERTEX3> vertices;
	vector<VERTEX2> uvs;
	vector<VERTEX3> normals;
	vector<int> indices;

	ifstream file(filepath, ifstream::in);
	if (!file.is_open()) 
		return;
	
	vector<string> lines;
	char buffer[256];

	while (!file.eof())
	{
		file.getline(buffer, 256);
		lines.push_back(string(buffer));
	}

	file.close();

	for (unsigned i = 0; i < lines.size(); i++)
	{
		string* str = &lines[i];
		if (str->size() < 2) continue;
		char first = (*str)[0];

		if (first == 'v')
		{
			char second = (*str)[1];
			if (second == 'n')//        normal
			{
				float x, y, z = 0.0f;
				sscanf_s(str->c_str(), "vn %f %f %f", &x, &y, &z);
				normals.push_back(VERTEX3(x, y, z));
			}
			else if (second == 't')//   uv point
			{
				float u, v = 0.0f;
				sscanf_s(str->c_str(), "vt %f %f", &u, &v);
				uvs.push_back(VERTEX2(u, v));
			}
			else//                      vertex
			{
				float x, y, z = 0.0f;
				sscanf_s(str->c_str(), "v %f %f %f", &x, &y, &z);
				vertices.push_back(VERTEX3(x, y, z));
			}
		}
		else if (first == 'f')//        face
		{
			int a, auv, an, b, buv, bn, c, cuv, cn;
			sscanf_s(str->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &a, &auv, &an, &b, &buv, &bn, &c, &cuv, &cn);
			indices.push_back(a);
			indices.push_back(auv);
			indices.push_back(an);
			indices.push_back(b);
			indices.push_back(buv);
			indices.push_back(bn);
			indices.push_back(c);
			indices.push_back(cuv);
			indices.push_back(cn);
		}
	}
	
	*outMesh = new MESHDATA(indices.size() / 3, filepath);

	for (unsigned i = 0; i < (*outMesh)->indices; i += 3)
	{
		(*outMesh)->indexBuffer[i] = i;
		(*outMesh)->indexBuffer[i + 1] = i + 1;
		(*outMesh)->indexBuffer[i + 2] = i + 2;
		unsigned vertexAIndex = indices[(i * 3) + 0] - 1;
		unsigned uvAIndex = indices[(i * 3) + 1] - 1;
		unsigned normalAIndex = indices[(i * 3) + 2] - 1;
		unsigned vertexBIndex = indices[((i + 1) * 3) + 0] - 1;
		unsigned uvBIndex = indices[((i + 1) * 3) + 1] - 1;
		unsigned normalBIndex = indices[((i + 1) * 3) + 2] - 1;
		unsigned vertexCIndex = indices[((i + 2) * 3) + 0] - 1;
		unsigned uvCIndex = indices[((i + 2) * 3) + 1] - 1;
		unsigned normalCIndex = indices[((i + 2) * 3) + 2] - 1;
		VERTEX3* vertexa = &vertices[vertexAIndex];
		VERTEX2* uva = &uvs[uvAIndex];
		VERTEX3* normala = &normals[normalAIndex];
		VERTEX3* vertexb = &vertices[vertexBIndex];
		VERTEX2* uvb = &uvs[uvBIndex];
		VERTEX3* normalb = &normals[normalBIndex];
		VERTEX3* vertexc = &vertices[vertexCIndex];
		VERTEX2* uvc = &uvs[uvCIndex];
		VERTEX3* normalc = &normals[normalCIndex];

		VERTEX3 tangenta = CalculateTangent(*normala, *vertexa, *vertexb, *vertexc, *uva);
		VERTEX3 tangentb = CalculateTangent(*normalb, *vertexb, *vertexc, *vertexa, *uvb);
		VERTEX3 tangentc = CalculateTangent(*normalc, *vertexc, *vertexa, *vertexb, *uvc);
		VERTEX3 binormala = CrossProduct(*normala, tangenta);
		VERTEX3 binormalb = CrossProduct(*normalb, tangentb);
		VERTEX3 binormalc = CrossProduct(*normalc, tangentc);

		MESHVERT* mverta = &(*outMesh)->vertBuffer[i];
		mverta->pos[0] = vertexa->x;
		mverta->pos[1] = vertexa->y;
		mverta->pos[2] = vertexa->z;
		mverta->pos[3] = 1.f;
		mverta->tex0[0] = uva->x;
		mverta->tex0[1] = 1.0f - uva->y;
		mverta->normal[0] = normala->x;
		mverta->normal[1] = normala->y;
		mverta->normal[2] = normala->z;
		mverta->tangent[0] = tangenta.x;
		mverta->tangent[1] = tangenta.y;
		mverta->tangent[2] = tangenta.z;
		mverta->binormal[0] = binormala.x;
		mverta->binormal[1] = binormala.y;
		mverta->binormal[2] = binormala.z;
		MESHVERT* mvertb = &(*outMesh)->vertBuffer[i + 1];
		mvertb->pos[0] = vertexb->x;
		mvertb->pos[1] = vertexb->y;
		mvertb->pos[2] = vertexb->z;
		mvertb->pos[3] = 1.f;
		mvertb->tex0[0] = uvb->x;
		mvertb->tex0[1] = 1.0f - uvb->y;
		mvertb->normal[0] = normalb->x;
		mvertb->normal[1] = normalb->y;
		mvertb->normal[2] = normalb->z;
		mvertb->tangent[0] = tangentb.x;
		mvertb->tangent[1] = tangentb.y;
		mvertb->tangent[2] = tangentb.z;
		mvertb->binormal[0] = binormalb.x;
		mvertb->binormal[1] = binormalb.y;
		mvertb->binormal[2] = binormalb.z;
		MESHVERT* mvertc = &(*outMesh)->vertBuffer[i + 2];
		mvertc->pos[0] = vertexc->x;
		mvertc->pos[1] = vertexc->y;
		mvertc->pos[2] = vertexc->z;
		mvertc->pos[3] = 1.f;
		mvertc->tex0[0] = uvc->x;
		mvertc->tex0[1] = 1.0f - uvc->y;
		mvertc->normal[0] = normalc->x;
		mvertc->normal[1] = normalc->y;
		mvertc->normal[2] = normalc->z;
		mvertc->tangent[0] = tangentc.x;
		mvertc->tangent[1] = tangentc.y;
		mvertc->tangent[2] = tangentc.z;
		mvertc->binormal[0] = binormalc.x;
		mvertc->binormal[1] = binormalc.y;
		mvertc->binormal[2] = binormalc.z;
	}
	
	vertices.clear();
	uvs.clear();
	normals.clear();
	indices.clear();
}