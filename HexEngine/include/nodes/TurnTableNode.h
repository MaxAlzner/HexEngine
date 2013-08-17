#ifndef _TURNTABLENODE_H_
#define _TURNTABLENODE_H_
HEX_BEGIN

class TurnTableNode : public ComponentNode
{
public:

	TurnTableNode();
	~TurnTableNode();
		
	void load();
	void unload();
	void destroy();
	
	void onStart();
	void onFrameUpdate();
	void onFixedUpdate();

	float turnSpeed;
};

HEX_END
#endif