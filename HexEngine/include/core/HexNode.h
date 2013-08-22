#ifndef _HEX_NODE_H_
#define _HEX_NODE_H_
HEX_BEGIN
	
HEX_API typedef enum COMPONENT
{
	COMPONENT_NONE                                             = 0x00000000, 
	
	COMPONENT_TRANSFORM                                        = 0x00000001, 
	COMPONENT_SHAPE                                            = 0x00000002, 
	COMPONENT_MATERIAL                                         = 0x00000003, 

	COMPONENT_CAMERA                                           = 0x00000010, 
	COMPONENT_LIGHT                                            = 0x00000020, 
	COMPONENT_SKYBOX                                           = 0x00000030, 
	
	COMPONENT_FIRSTPERSON                                      = 0x00000100, 
	COMPONENT_THIRDPERSON                                      = 0x00000200, 
	COMPONENT_TURNTABLE                                        = 0x00000300, 
};

HEX_API extern void GenEntities(uint size, uint* entities);
HEX_API extern void BindEntity(uint entity);
HEX_API extern void TransformEntity(float x, float y, float z, float rx = 0.0f, float ry = 0.0f, float rz = 0.0f);
HEX_API extern void ParentEntity(uint parent, uint child);

HEX_API extern void AddShape(uint mesh);
HEX_API extern void AddMaterial(uint color, uint normal = 0, uint specular = 0);

HEX_API extern void AddCamera(float fovAngle, float nearZ, float farZ);
HEX_API extern void AddDirectionalLight(float intensity);
HEX_API extern void AddPointLight(float intensity);

HEX_API extern void AddNode(COMPONENT parameter);

template <typename T> extern T* AddComponent();
template <typename T> extern T* GetComponent();

template <> extern CameraNode*      AddComponent<>();
template <> extern LightNode*       AddComponent<>();
template <> extern SkyboxNode*      AddComponent<>();
template <> extern FirstPersonNode* AddComponent<>();
template <> extern ThirdPersonNode* AddComponent<>();
template <> extern TurnTableNode*   AddComponent<>();

template <> extern CameraNode*      GetComponent<>();
template <> extern LightNode*       GetComponent<>();
template <> extern SkyboxNode*      GetComponent<>();
template <> extern FirstPersonNode* GetComponent<>();
template <> extern ThirdPersonNode* GetComponent<>();
template <> extern TurnTableNode*   GetComponent<>();
	
HEX_END
#endif