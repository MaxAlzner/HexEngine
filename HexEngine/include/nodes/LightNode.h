#ifndef _LIGHTNODE_H_
#define _LIGHTNODE_H_
HEX_BEGIN

HEX_API typedef enum HEX_LIGHTMODE
{
	HEX_LIGHTMODE_NONE         = 0, 
	HEX_LIGHTMODE_DIRECTIONAL  = 1, 
	HEX_LIGHTMODE_POINT        = 2, 
	HEX_LIGHTMODE_SPOT         = 3, 
};

class HEX_API LightNode : public ComponentNode
{
public:

	LightNode();
	~LightNode();
		
	void load();
	void destroy();
	
	void onFrameUpdate();
	void onFixedUpdate();

	HEX_LIGHTMODE mode;
	float intensity;
	MALib::COLOR color;
};

HEX_END
#endif