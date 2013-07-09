#ifndef _SKYBOXNODE_H_
#define _SKYBOXNODE_H_
HEX_BEGIN

class SkyboxNode : public ComponentNode
{
public:

	SkyboxNode();
	~SkyboxNode();
		
	void load();
	void unload();
	void destroy();
	
	void onStart();
	void onFrameUpdate();
	void onFixedUpdate();
};

HEX_END
#endif