#include "..\include\HexMain.h"

#ifdef _CAMERANODE_H_
HEX_BEGIN

CameraNode::CameraNode()
{
	this->type = COMPONENT_CAMERA;
	this->fovAngle = 45.0f;
	this->nearZ = 0.01f;
	this->farZ = 100.0f;
	this->perspective = glm::mat4(1.0f);
	this->viewSpace = glm::mat4(1.0f);
}
CameraNode::~CameraNode()
{
}
		
void CameraNode::load()
{
	if (this->root == NULL) return;
	if (this->root->transform == NULL) return;
	MainCamera = this;
	
	SetUniform(UNIFORM_WS_TO_CS, glm::value_ptr(this->viewSpace));
	SetUniform(UNIFORM_PROJECTION, glm::value_ptr(this->perspective));
}
void CameraNode::unload()
{
	MainCamera = NULL;
}
void CameraNode::destroy()
{
}

void CameraNode::onStart()
{
}
void CameraNode::onFrameUpdate()
{
	float aspect = float(ScreenRect.width) / float(ScreenRect.height);
	glm::vec3 eye = this->root->transform->position;
	glm::vec3 focus = eye + (this->root->transform->forward);
	this->viewSpace = glm::lookAt(eye, focus, this->root->transform->up);
	this->perspective = glm::perspective(this->fovAngle, aspect, this->nearZ, this->farZ);
}
void CameraNode::onFixedUpdate()
{
}

HEX_END
#endif