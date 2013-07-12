#include "..\include\HexMain.h"

#ifdef _CAMERANODE_H_
HEX_BEGIN

CameraNode::CameraNode()
{
	this->fovAngle = 45.0f;
	this->aspectRatio = 4.0f / 3.0f;
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
	
	glm::vec3 eye = this->root->transform->position;
	glm::vec3 focus = eye + (this->root->transform->forward);
	this->viewSpace = glm::lookAt(eye, focus, this->root->transform->up);
	this->perspective = glm::perspective(this->fovAngle, this->aspectRatio, this->nearZ, this->farZ);
	
	glm::mat4 billboard = glm::mat4(1.0f);
	billboard *= glm::rotate(-this->root->transform->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	billboard *= glm::rotate(this->root->transform->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	billboard *= glm::rotate(this->root->transform->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	SetUniform(UNIFORM_WS_TO_CS, glm::value_ptr(this->viewSpace));
	SetUniform(UNIFORM_BILLBOARD, glm::value_ptr(billboard));
	SetUniform(UNIFORM_PROJECTION, glm::value_ptr(this->perspective));
}
void CameraNode::unload()
{
}
void CameraNode::destroy()
{
}

void CameraNode::onStart()
{
}
void CameraNode::onFrameUpdate()
{
}
void CameraNode::onFixedUpdate()
{
}

HEX_END
#endif