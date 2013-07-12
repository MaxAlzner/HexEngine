#include "..\include\HexMain.h"

#ifdef _SKYBOXNODE_H_
HEX_BEGIN

SkyboxNode::SkyboxNode()
{
}
SkyboxNode::~SkyboxNode()
{
}
		
void SkyboxNode::load()
{
	/*glm::mat4 camera = glm::mat4(1.0f);
	camera = glm::rotate(camera, -MainCamera->root->transform->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	camera = glm::rotate(camera, MainCamera->root->transform->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	camera = glm::rotate(camera, MainCamera->root->transform->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));*/

	//SetUniform(UNIFORM_WS_TO_CS, glm::value_ptr(camera));
	//SetUniform(UNIFORM_PROJECTION, glm::value_ptr(MainCamera->perspective));
	SetUniform(UNIFORM_FLAG_BASECOLOR_RENDER);
	//glDisable(GL_DEPTH_TEST);
}
void SkyboxNode::unload()
{
	//glEnable(GL_DEPTH_TEST);
	SetUniform(UNIFORM_FLAG_PREVIOUS);
}
void SkyboxNode::destroy()
{
}
	
void SkyboxNode::onStart()
{
}
void SkyboxNode::onFrameUpdate()
{
}
void SkyboxNode::onFixedUpdate()
{
}

HEX_END
#endif