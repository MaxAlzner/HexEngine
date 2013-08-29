#ifndef _PANNODE_H_
#define _PANNODE_H_
HEX_BEGIN
	
class PanNode : public ComponentNode
{
public:

	PanNode();
	~PanNode();
		
	void load();
	void unload();
	void destroy();
	
	void onStart();
	void onFrameUpdate();
	void onFixedUpdate();

	float moveSpeed;
	glm::vec2 range;
	glm::vec3 boundsLeft;
	glm::vec3 boundsRight;
};

HEX_END
#endif