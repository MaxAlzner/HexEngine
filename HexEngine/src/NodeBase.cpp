#include "..\include\HexMain.h"

#ifdef _NODEBASE_H_
HEX_BEGIN

HEX_API void NodeBase::parentTo(HexEntity* obj)
{
	this->root = obj;
}

HEX_END
#endif