#ifndef _THIRDPERSONNODE_H_
#define _THIRDPERSONNODE_H_
HEX_BEGIN
	
class ThirdPersonNode : public ComponentNode
{
public:

	ThirdPersonNode();
	~ThirdPersonNode();
		
	void load();
	void unload();
	void destroy();
	
	void onStart();
	void onFrameUpdate();
	void onFixedUpdate();

	glm::vec2 sensitivity;
	glm::vec2 moveSpeed;
};

HEX_END
#endif