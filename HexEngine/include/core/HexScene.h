#ifndef _HEX_SCENE_H_
#define _HEX_SCENE_H_
HEX_BEGIN
	
struct Prefab;
typedef struct Prefab Prefab;
struct Scene;
typedef struct Scene Scene;

void LogPrefab(Prefab* prefab);
void LogScene(Scene* scene);

Scene* CreateScene(string filepath);
Prefab* CreatePrefab(string name);
void DestroyScene(Scene** scene);
void DestroyPrefab(Prefab** prefab);
void CopyPrefab(Prefab* dest, Prefab* src);

extern bool BuildPrefab(Prefab* prefab, uint* outEntity);
extern bool BuildScene(Scene* scene);

HEX_API extern Scene* LoadScene(const string filepath);
	
HEX_END
#endif