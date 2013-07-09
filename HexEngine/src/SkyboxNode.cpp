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
	SetUniform(UNIFORM_WS_TO_CS, glm::value_ptr(MainCamera->root->transform->space));
	SetUniform(UNIFORM_PROJECTION, glm::value_ptr(MainCamera->perspective));
	SetUniform(UNIFORM_FLAG_BASECOLOR_RENDER);
	glDisable(GL_DEPTH_TEST);
}
void SkyboxNode::unload()
{
	glEnable(GL_DEPTH_TEST);
	SetUniform(UNIFORM_FLAG_NONE);
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