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

	HEX_LIGHTMODE mode;
	float intensity;
	MALib::COLOR color;
	MALib::VEC3 falloff;
};

HEX_END
#endif