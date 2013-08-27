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
	
HEX_API typedef enum FILETYPE
{
	FILETYPE_NONE              = 0x00000000, 

	FILETYPE_OBJ               = 0x00000011, 
	FILETYPE_VMP               = 0x00000012, 
	FILETYPE_BMP               = 0x00000101, 
	FILETYPE_TGA               = 0x00000102, 
	
	FILETYPE_SCENE             = 0x00001001, 
};

#endif