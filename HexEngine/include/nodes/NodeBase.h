#ifndef _NODEBASE_H_
#define _NODEBASE_H_
HEX_BEGIN

class NodeBase
{
public:

	virtual void load() = 0;
	virtual void unload() = 0;
	virtual void destroy() = 0;

	virtual void parentTo(HexEntity* obj);

	COMPONENT type;
	HexEntity* root;
};

HEX_END
#endif