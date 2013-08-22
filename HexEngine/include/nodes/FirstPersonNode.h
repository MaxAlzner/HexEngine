#ifndef _FIRSTPERSONNODE_H_
#define _FIRSTPERSONNODE_H_
HEX_BEGIN
	
class FirstPersonNode : public ComponentNode
{
public:

	FirstPersonNode();
	~FirstPersonNode();
		
	void load();
	void unload();
	void destroy();
	
	void onStart();
	void onFrameUpdate();
	void onFixedUpdate();

	glm::vec2 rotation;
	glm::vec2 sensitivity;
	glm::vec2 moveSpeed;
	glm::vec2 rangeX;
	glm::vec2 rangeY;
};

HEX_END
#endif