#ifndef _SWIVELNODE_H_
#define _SWIVELNODE_H_
HEX_BEGIN

class SwivelNode : public ComponentNode
{
public:

	SwivelNode();
	~SwivelNode();
		
	void load();
	void unload();
	void destroy();
	
	void onStart();
	void onFrameUpdate();
	void onFixedUpdate();

	float turnSpeed;
	glm::vec2 range;
};

HEX_END
#endif