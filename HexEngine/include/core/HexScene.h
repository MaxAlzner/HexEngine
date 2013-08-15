#ifndef _HEX_SCENE_H_
#define _HEX_SCENE_H_
HEX_BEGIN
	
struct Scene;
typedef struct Scene Scene;

HEX_API extern bool LoadScene(const string filepath);
	
HEX_END
#endif