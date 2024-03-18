#pragma once

//#include <math.h>

#include <string>
#include <format>
#include <map>
#include <new>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <zlib.h>

#ifdef __GNUC__
#define sprintf_s snprintf
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),(mode)))==NULL
#endif

#ifndef _WIN32
#define _WIN32 0
#endif

#define FONT_PATH "appfont-MPLUSRounded1c-Medium.ttf"
#define FONT_PATH_JP "appfontjp-NotoSansJP-VariableFont_wght.ttf"

class EventCallbackListener;
class TextRenderer;
class MainEditor;
class EditorColorPicker;
class BaseScreen;
class BaseBrush;

extern int g_windowW, g_windowH;
extern SDL_Window* g_wd;
extern SDL_Renderer* g_rd;
extern TextRenderer* g_fnt;
extern int g_mouseX, g_mouseY;
extern std::vector<BaseBrush*> g_brushes;

void g_addScreen(BaseScreen* a);

struct XY {
	int x, y;
};

#include "platform.h"