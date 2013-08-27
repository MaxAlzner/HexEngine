#ifndef _HEX_GUI_H_
#define _HEX_GUI_H_
HEX_BEGIN

struct GUI;
typedef struct GUI GUI;
	
extern GUI* CreateGUI();
extern void DestroyGUI(GUI** gui);

HEX_API extern uint AddGUIText(const MALib::RECT& rect, const string text);
HEX_API extern uint AddGUIImage(const MALib::RECT& rect, uint texture);

HEX_API extern void HideGUI(uint gui);
HEX_API extern void ShowGUI(uint gui);
HEX_API extern void ToggleGUI(uint gui);

HEX_API extern void TransformGUI(uint gui, const MALib::RECT& rect);
HEX_API extern void AnimateGUI(uint gui, const MALib::RECT& rect, float delta);

HEX_API extern void InitializeGUI();
HEX_API extern void UninitializeGUI();

HEX_API extern void DrawGUI();

HEX_END
#endif