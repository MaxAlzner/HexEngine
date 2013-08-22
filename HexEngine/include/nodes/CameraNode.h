#ifndef _CAMERANODE_H_
#define _CAMERANODE_H_
HEX_BEGIN

class CameraNode : public ComponentNode
{
public:

	CameraNode();
	~CameraNode();
		
	void load();
	void unload();
	void destroy();
	
	void onStart();
	void onFrameUpdate();
	void onFixedUpdate();

	float fovAngle;
	float nearZ;
	float farZ;

	glm::mat4 perspective;
	glm::mat4 viewSpace;
};

HEX_END
#endif