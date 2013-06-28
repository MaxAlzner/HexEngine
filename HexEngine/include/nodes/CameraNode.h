#ifndef _CAMERANODE_H_
#define _CAMERANODE_H_
HEX_BEGIN

class HEX_API CameraNode : public ComponentNode
{
public:

	CameraNode();
	~CameraNode();
		
	void load();
	void destroy();
	
	void onFrameUpdate();
	void onFixedUpdate();

	float fovAngle;
	float aspectRatio;
	float nearZ;
	float farZ;
};

HEX_END
#endif