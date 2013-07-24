#ifndef _CONTROLNODE_H_
#define _CONTROLNODE_H_
HEX_BEGIN
	
class ControlNode : public ComponentNode
{
public:

	ControlNode();
	~ControlNode();
		
	void load();
	void unload();
	void destroy();
	
	void onStart();
	void onFrameUpdate();
	void onFixedUpdate();

	glm::vec2 rotation;
	glm::vec2 sensitivity;
};

HEX_END
#endif