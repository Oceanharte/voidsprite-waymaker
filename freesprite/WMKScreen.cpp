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

    std::vector<SDL_Rect> rects = {
    { 32, 32, 32, 640 },
    { 80, 32, 32, 640 },
    { g_windowW / 4, 32, 640, 416 },
    { 128, 32, (g_windowW / 4) - 144, 416 },
    { (g_windowW / 4) + 656 , 32, (g_windowW / 4) - 144, 416 },
    { 128, 464, (g_windowW / 4) - 144, 208 },
    { g_windowW / 4, 464, 208, 208 },
    { (g_windowW / 4) + 432, 464, 208, 208 },
    { (g_windowW / 4) + 12, 368, 201, 64 },
    { (g_windowW / 4) + 221, 368, 201, 64 },
    { (g_windowW / 4) + 427, 368, 201, 64 },
    { (g_windowW / 4) + 12, 48, 201, 64 },
    { (g_windowW / 4) + 221, 48, 201, 64 },
    { (g_windowW / 4) + 427, 48, 201, 64 }
    };

    SDL_Color colorR1 = { 0x30, 0x30, 0x30, 0xa0};
    SDL_Color colorR2 = { 0x20, 0x20, 0x20, 0xa0};
    SDL_Color colorR3 = { 0x10, 0x10, 0x10, 0xa0 };
    SDL_Color bkColour1 = { 0x30, 0x30, 0x30, 0xa2};
    SDL_Color bkColour2 = { 0x20, 0x20, 0x20, 0xa2};
    SDL_Color bkColour3 = { 0x10, 0x10, 0x10, 0xa2};
    SDL_Color bkStat1 = { 0x20, 0x20, 0x20, 0xFF};
    SDL_Color bkStat2 = { 0x0, 0x0, 0x0, 0xFF};
    SDL_Color bkStat3 = { 0x0, 0x0, 0x0, 0xFF};

    SDL_SetRenderDrawColor(g_rd, 0xff, 0xff, 0xff, 0x80);
    
    for (int i = 0; i < rects.size(); i++) {
        switch (i) {
        case 0:
        case 1:
            renderGradient(rects[i], sdlcolorToUint32(colorR3), sdlcolorToUint32(colorR2), sdlcolorToUint32(colorR2), sdlcolorToUint32(colorR1));
            break;
        case 2:
            renderGradient(rects[i], sdlcolorToUint32(bkColour1), sdlcolorToUint32(bkColour2), sdlcolorToUint32(bkColour3), sdlcolorToUint32(bkColour1));
            break;
        default:
            renderGradient(rects[i], sdlcolorToUint32(bkStat1), sdlcolorToUint32(bkStat2), sdlcolorToUint32(bkStat3), sdlcolorToUint32(bkStat2));
            break;
        }
        SDL_RenderDrawRect(g_rd, &rects[i]);
    }

    g_fnt->RenderString("Combat Viewport", g_windowW/4, 8);
    g_fnt->RenderString("Combat Log", (g_windowW/4)+656, 8);
    g_fnt->RenderString("Payload Cache", 128, 8);
    g_fnt->RenderString("Run Status:", 128, 464);

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