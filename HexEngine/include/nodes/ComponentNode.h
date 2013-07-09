#ifndef _COMPONENTNODE_H_
#define _COMPONENTNODE_H_
HEX_BEGIN

class ComponentNode : public NodeBase
{
public:
	
	virtual void onStart() = 0;
	virtual void onFrameUpdate() = 0;
	virtual void onFixedUpdate() = 0;
};

HEX_END
#endif