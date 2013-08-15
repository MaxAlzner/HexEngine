#ifndef _HEX_SCENE_H_
#define _HEX_SCENE_H_
HEX_BEGIN
	
struct Scene;
typedef struct Scene Scene;
struct Prefab;
typedef struct Prefab Prefab;

HEX_API extern bool LoadScene(const string filepath);
HEX_API extern bool LoadScene(MALib::TEXTFILE* file);
	
HEX_END
#endif