#include "..\include\HexMain.h"

#ifdef _CAMERANODE_H_
HEX_BEGIN

HEX_API CameraNode::CameraNode()
{
	this->fovAngle = 45.0f;
	this->aspectRatio = 4.0f / 3.0f;
	this->nearZ = 0.01f;
	this->farZ = 100.0f;
}
HEX_API CameraNode::~CameraNode()
{
}
		
HEX_API void CameraNode::load()
{
	if (this->root == NULL) return;
	if (this->root->transform == NULL) return;
	
	glm::vec3 eye = this->root->transform->translation;
	glm::mat4 persp = glm::perspective(this->fovAngle, this->aspectRatio, this->nearZ, this->farZ);
	glm::mat4 view = glm::lookAt(eye, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	SetUniform(HEX_UNIFORM_WS_TO_CS, glm::value_ptr(view));
	SetUniform(HEX_UNIFORM_PROJECTION, glm::value_ptr(persp));
}
HEX_API void CameraNode::destroy()
{
}

HEX_API void CameraNode::onFrameUpdate()
{
}
HEX_API void CameraNode::onFixedUpdate()
{
}

HEX_END
#endif