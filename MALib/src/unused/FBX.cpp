#include "StdAfx.h"

FbxManager* FBX::SDKMANAGER = NULL;

void FBX::Initialize()
{
	FBX::SDKMANAGER = FbxManager::Create();

	if (FBX::SDKMANAGER == NULL) return;
	FbxIOSettings* ios = FbxIOSettings::Create(FBX::SDKMANAGER, IOSROOT);
	FBX::SDKMANAGER->SetIOSettings(ios);
}
void FBX::Uninitialize()
{
	if (FBX::SDKMANAGER != NULL) FBX::SDKMANAGER->Destroy();
}

void FBX::Import(const char* filepath, MESHDATA** outMesh)
{
	if (filepath == NULL) return;
	if (outMesh == NULL) return;

	FbxScene* scene = FbxScene::Create(FBX::SDKMANAGER, "Empty Scene");

	int fileMajor, fileMinor, fileRevision;
	int sdkmajor,  sdkminor,  sdkrevision;
	bool status;
	
	FbxManager::GetFileFormatVersion(sdkmajor,  sdkminor,  sdkrevision);
	FbxImporter* importer = FbxImporter::Create(FBX::SDKMANAGER, "");
	const bool importStatus = importer->Initialize(filepath, -1, FBX::SDKMANAGER->GetIOSettings());
	importer->GetFileVersion(fileMajor, fileMinor, fileRevision);

	if(!importStatus) 
		return;
	status = importer->Import(scene);
	importer->Destroy();
	
	FbxNode* rootNode = scene->GetRootNode();
	vector<FbxNode*> nodes;
	nodes.push_back(rootNode);
	for (int i = 0; i < rootNode->GetChildCount(); i++) 
		nodes.push_back(rootNode->GetChild(i));

	for (unsigned i = 0; i < nodes.size(); i++)
	{
		FbxNode* node = nodes[i];
		FbxMesh* mesh = node->GetMesh();
		if (mesh == NULL) continue;
		
		unsigned vertCount = mesh->GetControlPointsCount();
		if (vertCount <= 0) continue;

		FBX::Extract(mesh, outMesh);

		return;
	}
	nodes.clear();
}
MESHDATA* FBX::Import(const char* filepath)
{
	MESHDATA* mesh = NULL;
	FBX::Import(filepath, &mesh);
	return mesh;
}
void FBX::Import(void* data, int size, MESHDATA** outMesh)
{
	if (data == NULL) return;
	if (outMesh == NULL) return;

	FbxScene* scene = FbxScene::Create(FBX::SDKMANAGER, "Empty Scene");

	int fileMajor, fileMinor, fileRevision;
	int sdkmajor,  sdkminor,  sdkrevision;
	bool status;
	
	FbxManager::GetFileFormatVersion(sdkmajor,  sdkminor,  sdkrevision);
#if 0
	FbxStream stream;
	if (stream.Write(data, size) <= 0) return;
	FbxImporter* importer = FbxImporter::Create(FBX::SDKMANAGER, "");
	const bool importStatus = importer->Initialize(&stream, data, -1, FBX::SDKMANAGER->GetIOSettings());
	importer->GetFileVersion(fileMajor, fileMinor, fileRevision);

	if(!importStatus) 
		return;
	status = importer->Import(scene);
	importer->Destroy();
#else
	return;
#endif
	
	FbxNode* rootNode = scene->GetRootNode();
	vector<FbxNode*> nodes;
	nodes.push_back(rootNode);
	for (int i = 0; i < rootNode->GetChildCount(); i++) 
		nodes.push_back(rootNode->GetChild(i));

	for (unsigned i = 0; i < nodes.size(); i++)
	{
		FbxNode* node = nodes[i];
		FbxMesh* mesh = node->GetMesh();
		if (mesh == NULL) continue;
		
		unsigned vertCount = mesh->GetControlPointsCount();
		if (vertCount <= 0) continue;

		FBX::Extract(mesh, outMesh);

		return;
	}
	nodes.clear();
}
MESHDATA* FBX::Import(void* data, int size)
{
	MESHDATA* mesh = NULL;
	FBX::Import(data, size, &mesh);
	return mesh;
}

void FBX::Extract(FbxMesh* mesh, MESHDATA** outMesh)
{
	if (mesh == NULL) return;
	if (outMesh == NULL) return;
	
	const int polyCount = mesh->GetPolygonCount();
	FbxVector4* VertexArray = (FbxVector4*)mesh->GetControlPoints();
	
	FbxStringList UVSetNameList;
	mesh->GetUVSetNames(UVSetNameList);
	if (UVSetNameList.GetCount() < 1) 
		return;
	const char* UVSetName = UVSetNameList.GetStringAt(0);

	FbxGeometryElementTangent* TangentElement = mesh->GetElementTangent();
	if (TangentElement == NULL) return;

	unsigned int indices = polyCount * 3;
	*outMesh = new MESHDATA();
	(*outMesh)->indices = indices;
	(*outMesh)->indexBuffer = new MESHINDEX[indices];
	(*outMesh)->vertBuffer = new MESHVERT[indices];
	ZeroMemory((*outMesh)->indexBuffer, indices * sizeof(MESHINDEX));
	ZeroMemory((*outMesh)->vertBuffer, indices * sizeof(MESHVERT));

	int indexByPolygonVertex = 0;
	for (int polyIndex = 0; polyIndex < polyCount; polyIndex++)
	{
		for (int vertIndex = 0; vertIndex < 3; vertIndex++)
		{
			const int vertexIndex = mesh->GetPolygonVertex(polyIndex, vertIndex);
			FbxVector4 vertex = VertexArray[vertexIndex];
			FbxVector4 normal;
			FbxVector2 uv;
			mesh->GetPolygonVertexNormal(polyIndex, vertIndex, normal);
			mesh->GetPolygonVertexUV(polyIndex, vertIndex, UVSetName, uv);

			int n = 0;
			if(TangentElement->GetReferenceMode() == FbxGeometryElement::eDirect)
				n = indexByPolygonVertex;
			if(TangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
				n = TangentElement->GetIndexArray().GetAt(indexByPolygonVertex);
			FbxVector4 tangent = TangentElement->GetDirectArray().GetAt(n);

			FbxVector4 binormal = normal.CrossProduct(tangent);

			unsigned int index = (polyIndex * 3) + vertIndex;
			(*outMesh)->indexBuffer[index] = index;
			MESHVERT* mvert = &(*outMesh)->vertBuffer[index];
			mvert->pos[0] = float(vertex.mData[0]);
			mvert->pos[1] = float(vertex.mData[1]);
			mvert->pos[2] = float(vertex.mData[2]);
			mvert->pos[3] = float(vertex.mData[3]);
			mvert->tex0[0] = float(uv.mData[0]);
			mvert->tex0[1] = float(1.f - uv.mData[1]);
			mvert->normal[0] = float(normal.mData[0]);
			mvert->normal[1] = float(normal.mData[1]);
			mvert->normal[2] = float(normal.mData[2]);
			mvert->tangent[0] = float(tangent.mData[0]);
			mvert->tangent[1] = float(tangent.mData[1]);
			mvert->tangent[2] = float(tangent.mData[2]);
			mvert->binormal[0] = float(binormal.mData[0]);
			mvert->binormal[1] = float(binormal.mData[1]);
			mvert->binormal[2] = float(binormal.mData[2]);

			indexByPolygonVertex++;
		}
	}
}
	
#if 0
void FBX::ExtractVertices(FbxMesh* mesh, MESHDATA** outMesh)
{
	if (mesh == NULL) return;
	if (outMesh == NULL) return;

	unsigned vertCount = mesh->GetControlPointsCount();
	FbxVector4* VertexArray = (FbxVector4*)mesh->GetControlPoints();

	for (unsigned k = 0; k < vertCount; k++)
	{
		MESHVERT* mvert = &(*outMesh)->vertBuffer[k];
		FbxVector4* vertex = &VertexArray[k];
		mvert->pos[0] = vertex->mData[0];
		mvert->pos[1] = vertex->mData[1];
		mvert->pos[2] = vertex->mData[2];
		mvert->pos[3] = vertex->mData[3];
	}
}
void FBX::ExtractIndices(FbxMesh* mesh, MESHDATA** outMesh)
{
	if (mesh == NULL) return;
	if (outMesh == NULL) return;

	const int polyCount = mesh->GetPolygonCount();
	unsigned indices = polyCount * 3;
	if ((*outMesh)->indexBuffer != NULL) delete [] (*outMesh)->indexBuffer;
	(*outMesh)->indices = indices;
	(*outMesh)->indexBuffer = new MESHINDEX[indices];
	for (unsigned i = 0; i < polyCount; i++)
	{
		const int vertCount = mesh->GetPolygonSize(i);
		if (vertCount != 3) continue;
		(*outMesh)->indexBuffer[(i * 3) + 0] = mesh->GetPolygonVertex(i, 0);
		(*outMesh)->indexBuffer[(i * 3) + 1] = mesh->GetPolygonVertex(i, 1);
		(*outMesh)->indexBuffer[(i * 3) + 2] = mesh->GetPolygonVertex(i, 2);
	}
}
void FBX::ExtractUVs(FbxMesh* mesh, MESHDATA** outMesh)
{
	if (mesh == NULL) return;
	if (outMesh == NULL) return;
	
	FbxStringList UVSetNameList;
	mesh->GetUVSetNames(UVSetNameList);
	for (int i = 0; i < UVSetNameList.GetCount(); i++)
	{
		const char* UVSetName = UVSetNameList.GetStringAt(i);
		const FbxGeometryElementUV* UVElement = mesh->GetElementUV(UVSetName);

		if(!UVElement) continue;
		if(UVElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex) 
			continue;

		const bool useIndex = UVElement->GetReferenceMode() != FbxGeometryElement::eDirect;
		const int indexCount = (useIndex) ? UVElement->GetIndexArray().GetCount() : 0;
		const int polyCount = mesh->GetPolygonCount();
		
		int polyIndexCounter = 0;
		for (int polyIndex = 0; polyIndex < polyCount; polyIndex++)
		{
			const int polySize = mesh->GetPolygonSize(polyIndex);
			for (int vertIndex = 0; vertIndex < polySize; vertIndex++)
			{
				int UVIndex = useIndex ? UVElement->GetIndexArray().GetAt(polyIndexCounter) : polyIndexCounter;
				polyIndexCounter++;

				FbxVector2 uv = UVElement->GetDirectArray().GetAt(UVIndex);
				int vertexIndex = mesh->GetPolygonVertex(polyIndex, vertIndex);
				
				MESHVERT* mvert = &(*outMesh)->vertBuffer[vertexIndex];
				mvert->tex0[0] = uv.mData[0];
				mvert->tex0[1] = 1.0f - uv.mData[1];
			}
		}
	}
}
void FBX::ExtractNormals(FbxMesh* mesh, MESHDATA** outMesh)
{
	if (mesh == NULL) return;
	if (outMesh == NULL) return;

	FbxGeometryElementNormal* NormalElement = mesh->GetElementNormal();
	if (NormalElement == NULL) return;

	if(NormalElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		int vertCount = mesh->GetControlPointsCount();
		for(int vertIndex = 0; vertIndex < vertCount; vertIndex++)
		{
			int n = 0;
			if(NormalElement->GetReferenceMode() == FbxGeometryElement::eDirect) 
				n = vertIndex;
			if(NormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect) 
				n = NormalElement->GetIndexArray().GetAt(vertIndex);

			FbxVector4 normal = NormalElement->GetDirectArray().GetAt(n);
			MESHVERT* mvert = &(*outMesh)->vertBuffer[vertIndex];
			mvert->normal[0] = normal.mData[0];
			mvert->normal[1] = normal.mData[1];
			mvert->normal[2] = normal.mData[2];
		}
	}
	else if(NormalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		int indexByPolygonVertex = 0;
		for(int polygonIndex = 0; polygonIndex < mesh->GetPolygonCount(); polygonIndex++)
		{
			int polygonSize = mesh->GetPolygonSize(polygonIndex);
			for(int i = 0; i < polygonSize; i++)
			{
				int n = 0;

				if(NormalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
					n = indexByPolygonVertex;
				if(NormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
					n = NormalElement->GetIndexArray().GetAt(indexByPolygonVertex);

				FbxVector4 normal = NormalElement->GetDirectArray().GetAt(n);
				int vertexIndex = mesh->GetPolygonVertex(polygonIndex, i);
				MESHVERT* mvert = &(*outMesh)->vertBuffer[vertexIndex];
				mvert->normal[0] = normal.mData[0];
				mvert->normal[1] = normal.mData[1];
				mvert->normal[2] = normal.mData[2];
				
				indexByPolygonVertex++;
			}
		}
	}
}
void FBX::ExtractTangents(FbxMesh* mesh, MESHDATA** outMesh)
{
	if (mesh == NULL) return;
	if (outMesh == NULL) return;

	FbxGeometryElementTangent* TangentElement = mesh->GetElementTangent();
	if (TangentElement == NULL) return;

	if(TangentElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		int vertCount = mesh->GetControlPointsCount();
		for(int vertIndex = 0; vertIndex < vertCount; vertIndex++)
		{
			int n = 0;
			if(TangentElement->GetReferenceMode() == FbxGeometryElement::eDirect) 
				n = vertIndex;
			if(TangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect) 
				n = TangentElement->GetIndexArray().GetAt(vertIndex);

			FbxVector4 tangent = TangentElement->GetDirectArray().GetAt(n);
			MESHVERT* mvert = &(*outMesh)->vertBuffer[vertIndex];
			mvert->tangent[0] = tangent.mData[0];
			mvert->tangent[1] = tangent.mData[1];
			mvert->tangent[2] = tangent.mData[2];
		}
	}
	else if(TangentElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		int indexByPolygonVertex = 0;
		for(int polygonIndex = 0; polygonIndex < mesh->GetPolygonCount(); polygonIndex++)
		{
			int polygonSize = mesh->GetPolygonSize(polygonIndex);
			for(int i = 0; i < polygonSize; i++)
			{
				int n = 0;

				if(TangentElement->GetReferenceMode() == FbxGeometryElement::eDirect)
					n = indexByPolygonVertex;
				if(TangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
					n = TangentElement->GetIndexArray().GetAt(indexByPolygonVertex);

				FbxVector4 tangent = TangentElement->GetDirectArray().GetAt(n);
				int vertexIndex = mesh->GetPolygonVertex(polygonIndex, i);
				MESHVERT* mvert = &(*outMesh)->vertBuffer[vertexIndex];
				mvert->tangent[0] = tangent.mData[0];
				mvert->tangent[1] = tangent.mData[1];
				mvert->tangent[2] = tangent.mData[2];
				
				indexByPolygonVertex++;
			}
		}
	}
}
void FBX::ExtractBinormals(FbxMesh* mesh, MESHDATA** outMesh)
{
	if (mesh == NULL) return;
	if (outMesh == NULL) return;

	unsigned vertCount = mesh->GetControlPointsCount();
	for (unsigned i = 0; i < vertCount; i++)
	{
		MESHVERT* mvert = &(*outMesh)->vertBuffer[i];

		VERTEX3 normal(mvert->normal[0], mvert->normal[1], mvert->normal[2]);
		VERTEX3 tangent(mvert->tangent[0], mvert->tangent[1], mvert->tangent[2]);
		VERTEX3 binormal = CrossProduct(normal, tangent);

		mvert->binormal[0] = binormal.x;
		mvert->binormal[1] = binormal.y;
		mvert->binormal[2] = binormal.z;
	}
}
#endif