#ifndef _HEX_SCENE_H_
#define _HEX_SCENE_H_
HEX_BEGIN
	
struct Prefab;
typedef struct Prefab Prefab;
struct Scene;
typedef struct Scene Scene;

extern bool BuildPrefab(Prefab* prefab, uint* outEntity);
extern bool BuildScene(Scene* scene);

HEX_API extern bool LoadScene(const string filepath);
	
HEX_END
#endif