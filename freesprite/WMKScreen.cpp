#include "WMKScreen.h"
#include "FontRenderer.h"
#include "FileIO.h"
#include "PopupMessageBox.h"
#include "Notification.h"
#include "EventCallbackListener.h"
#include "FontRenderer.h"



void WMKScreen::tick() {
    if (closeNextTick) {
        g_closeScreen(this);
    }
}

void WMKScreen::render() {
    DrawBackground();

    SDL_Rect prgAll = SDL_Rect{ 32, 32, 32, 640 };
    SDL_Rect prgAllout = SDL_Rect{ 32, 32, 32, 640 };
    SDL_Rect prgInst = SDL_Rect{ 80, 32, 32, 640 };
    SDL_Rect prgInstout = SDL_Rect{ 80, 32, 32, 640 };
    SDL_Color colorR1 = { 0x30, 0x30, 0x30, 0xa0};
    SDL_Color colorR2 = { 0x20, 0x20, 0x20, 0xa0};
    SDL_Color colorR3 = { 0x10, 0x10, 0x10, 0xa0 };
    renderGradient(prgAll, sdlcolorToUint32(colorR3), sdlcolorToUint32(colorR2), sdlcolorToUint32(colorR2), sdlcolorToUint32(colorR1));
    renderGradient(prgInst, sdlcolorToUint32(colorR3), sdlcolorToUint32(colorR2), sdlcolorToUint32(colorR2), sdlcolorToUint32(colorR1));
    SDL_SetRenderDrawColor(g_rd, 0xff, 0xff, 0xff, 0x80);
    SDL_RenderDrawRect(g_rd, &prgAllout);
    SDL_RenderDrawRect(g_rd, &prgInstout);
}

void WMKScreen::takeInput(SDL_Event evt)
{

}

void WMKScreen::DrawBackground()
{
    uint32_t colorBG1 = 0xFF000000 | (sdlcolorToUint32(backgroundColor) == 0xFF000000 ? 0x000000 : 0xDFDFDF);
    uint32_t colorBG2 = 0xFF000000 | (sdlcolorToUint32(backgroundColor) == 0xFF000000 ? 0x202020 : 0x808080);
    renderGradient({ 0,0, g_windowW, g_windowH }, colorBG1, colorBG1, colorBG1, colorBG2);

    uint64_t bgtimer = g_config.animatedBackground >= 3 ? 0 : SDL_GetTicks64();
    if (g_config.animatedBackground == 1 || g_config.animatedBackground == 3) {
        int lineX = 400;
        for (int x = 40 + (bgtimer % 5000 / 5000.0 * 60); x < g_windowW + lineX; x += 60) {
            SDL_SetRenderDrawColor(g_rd, 0xff - backgroundColor.r, 0xff - backgroundColor.g, 0xff - backgroundColor.b, 0x40);
            SDL_RenderDrawLine(g_rd, x, 0, x - lineX, g_windowH);
            SDL_SetRenderDrawColor(g_rd, 0xff - backgroundColor.r, 0xff - backgroundColor.g, 0xff - backgroundColor.b, 0x0d);
            SDL_RenderDrawLine(g_rd, g_windowW - x, 0, g_windowW - x + lineX / 4 * 6, g_windowH);
        }
    }
   
}