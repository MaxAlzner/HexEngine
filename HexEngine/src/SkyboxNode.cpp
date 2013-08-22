#include "..\include\HexMain.h"

#ifdef _SKYBOXNODE_H_
HEX_BEGIN

SkyboxNode::SkyboxNode()
{
	this->type = COMPONENT_SKYBOX;
}
SkyboxNode::~SkyboxNode()
{
}
		
void SkyboxNode::load()
{
	/*if (CurrentFlag == UNIFORM_FLAG_NORMAL) */SetUniform(UNIFORM_FLAG_BASECOLOR_RENDER);
	//glDisable(GL_DEPTH_TEST);
}
void SkyboxNode::unload()
{
	//glEnable(GL_DEPTH_TEST);
	/*if (CurrentFlag == UNIFORM_FLAG_NORMAL) */SetUniform(UNIFORM_FLAG_PREVIOUS);
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