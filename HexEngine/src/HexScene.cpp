#include "..\include\HexMain.h"

#ifdef _HEX_SCENE_H_
HEX_BEGIN

MALib::ARRAY<uint> MeshSlots;
MALib::ARRAY<uint> TextureSlots;
	
HEX_API void LoadScene(const string filepath)
{
	if (filepath == 0) return;
	MALib::TEXTFILE* file = 0;
	if (!MALib::ImportTextFile(filepath, &file)) return;
	LoadScene(file);
	MALib::FreeTextFile(&file);
}
HEX_API void LoadScene(MALib::TEXTFILE* file)
{
	if (file == 0) return;

	for (uint i = 0; i < file->lines.length(); i++)
	{
	}
}

HEX_END
#endif