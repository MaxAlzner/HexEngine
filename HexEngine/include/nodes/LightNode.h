#ifndef _LIGHTNODE_H_
#define _LIGHTNODE_H_
HEX_BEGIN

HEX_API typedef enum HEX_LIGHTMODE
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

	HEX_LIGHTMODE mode;
	float intensity;
	MALib::COLOR color;
	MALib::VEC3 falloff;
};

HEX_END
#endif