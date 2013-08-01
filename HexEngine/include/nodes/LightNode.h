#ifndef _LIGHTNODE_H_
#define _LIGHTNODE_H_
HEX_BEGIN

HEX_API typedef enum LIGHTMODE
{
	LIGHTMODE_NONE         = 0, 
	LIGHTMODE_DIRECTIONAL  = 1, 
	LIGHTMODE_POINT        = 2, 
	LIGHTMODE_SPOT         = 3, 
};

class LightNode : public ComponentNode
{
public:

	LightNode();
	~LightNode();
		
	void load();
	void unload();
	void destroy();
	
	void onStart();
	void onFrameUpdate();
	void onFixedUpdate();

	LIGHTMODE mode;
	float intensity;
	MALib::COLOR color;
	glm::vec3 falloff;
};

HEX_END
#endif