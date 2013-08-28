#include "../include/HexMain.h"

#ifdef _HEX_GUI_H_
HEX_BEGIN

typedef struct GUI
{
	GUI()
	{
		memset(this, 0, sizeof(GUI));
	}
	MALib::RECT rect;
	uint texture;
	uint colorMap;
	MALib::COLOR color;
	string text;
	bool hidden;
} GUI;
	
GUI* CreateGUI()
{
	GUI* gui = new GUI;
	return gui;
}
void DestroyGUI(GUI** gui)
{
	if (gui == 0) return;
	delete *gui;
	*gui = 0;
}

HEX_API bool SetFontSheet(const string filepath, uint cellWidth, uint cellHeight)
{
	if (filepath == 0 || cellWidth == 0 || cellHeight == 0) return false;

	FILETYPE type = GetFiletype(filepath);
	if (type == FILETYPE_BMP)      RegisterBMP(&FontTexture, filepath);
	else if (type == FILETYPE_TGA) RegisterTGA(&FontTexture, filepath);
	else return false;

	return true;
}

HEX_API uint AddGUIText(const MALib::RECT& rect, const string text)
{
	if (text == 0 || strlen(text) < 1) return 0;

	GUI* gui = CreateGUI();
	gui->rect = rect;
	gui->color = MALib::COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	gui->text = text;
	gui->texture = FontTexture;

	ActiveGUI.add(gui);
	return ActiveGUI.length();
}
HEX_API uint AddGUIImage(const MALib::RECT& rect, uint texture)
{
	if (texture == 0) return 0;

	GUI* gui = CreateGUI();
	gui->rect = rect;
	gui->color = MALib::COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	gui->texture = texture;

	ActiveGUI.add(gui);
	return ActiveGUI.length();
}

HEX_API void HideGUI(uint gui)
{
	if (gui == 0 || gui >= ActiveGUI.length()) return;
	uint index = gui - 1;
	ActiveGUI[index]->hidden = true;
}
HEX_API void ShowGUI(uint gui)
{
	if (gui == 0 || gui >= ActiveGUI.length()) return;
	uint index = gui - 1;
	ActiveGUI[index]->hidden = false;
}
HEX_API void ToggleGUI(uint gui)
{
	if (gui == 0 || gui >= ActiveGUI.length()) return;
	uint index = gui - 1;
	GUI* hide = ActiveGUI[index];
	hide->hidden = !hide->hidden;
}

HEX_API void TransformGUI(uint gui, const MALib::RECT& rect)
{
	if (gui == 0 || gui >= ActiveGUI.length()) return;
	uint index = gui - 1;
	ActiveGUI[index]->rect = rect;
}
HEX_API void AnimateGUI(uint gui, const MALib::RECT& rect, float delta)
{
}

HEX_API void InitializeGUI()
{
	static float plane[24] = 
	{
		1.0f, 1.0f, 0.0f, 1.0f, 
		0.0f, 1.0f, 0.0f, 1.0f, 
		1.0f, 0.0f, 0.0f, 1.0f, 
		0.0f, 1.0f, 0.0f, 1.0f, 
		0.0f, 0.0f, 0.0f, 1.0f, 
		1.0f, 0.0f, 0.0f, 1.0f, 
	};

	glGenVertexArrays(1, &GUIVAO);
	glBindVertexArray(GUIVAO);
	glGenBuffers(1, &GUIBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, GUIBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GUIBuffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), plane, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}
HEX_API void UninitializeGUI()
{
	if (GUIBuffer != 0) glDeleteBuffers(1, &GUIBuffer);
	if (GUIVAO != 0) glDeleteVertexArrays(1, &GUIVAO);
}

void StartGUI()
{
	for (uint i = 0; i < ActiveGUI.length(); i++)
	{
		GUI* gui = ActiveGUI[i];
		if (gui == 0 || gui->texture == 0) continue;

		MaterialNode::BuildTexture(&gui->colorMap, GetTexture(gui->texture));
	}
}
void DrawGUI(GUI* gui)
{
	if (gui == 0 || gui->hidden) return;
	glBindVertexArray(GUIVAO);
		
	static float offset[2] = {float(gui->rect.x0) / float(ScreenRect.width), float(gui->rect.y0) / float(ScreenRect.height)};
	static float dimensions[2] = {float(gui->rect.width) / float(ScreenRect.width), float(gui->rect.height) / float(ScreenRect.height)};

	SetUniform(UNIFORM_GUI_POSITION, offset);
	SetUniform(UNIFORM_GUI_SCALE, dimensions);
	SetUniform(UNIFORM_OVERLAY_COLOR, &gui->color);
	SetTextureSlot(UNIFORM_TEXTURE_COLOR_MAP, gui->colorMap);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}

HEX_END
#endif