#ifndef _HEX_DEF_H_
#define _HEX_DEF_H_

#define HEX_API __declspec(dllexport)

#define HEX_BEGIN namespace HEX\
	{\
		class HexEntity;\
		HEX_API enum PARAMETER;\
		HEX_API enum COMPONENT;\
		HEX_API enum UNIFORM;
#define HEX_END }

#endif