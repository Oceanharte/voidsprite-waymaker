#include "WMKScreen.h"
#include "FontRenderer.h"
#include "FileIO.h"
#include "PopupMessageBox.h"
#include "Notification.h"
#include "EventCallbackListener.h"
#include "FontRenderer.h"
#include "WMKPlayer.h"
#include "WMKEnemy.h"


plrStats dpsdealer;
plrStats tank;
plrStats support;

int playerSel = 0;
int hp = 20;

std::vector<plrStats>party = {
    dpsdealer,
    support,
    tank
};

std::vector<enStats> combat;

std::random_device rd;
std::mt19937 gen(rd());

std::vector<SDL_Rect> rects = {
    { 32, 32, 32, 640 },
    { 80, 32, 32, 640 },
    { g_windowW / 4, 32, 640, 416 },
    { 128, 32, (g_windowW / 4) - 144, 416 },
    { (g_windowW / 4) + 656 , 32, (g_windowW / 4) - 144, 416 },
    { 128, 464, (g_windowW / 4) - 144, 208 },
    { g_windowW / 4, 464, 208, 208 },
    { (g_windowW / 4)+656, 464, (g_windowW / 4) - 144, 208 },
    { (g_windowW / 4) + 432, 464, 208, 208 },
    { (g_windowW / 4) + 12, 368, 201, 64 },
    { (g_windowW / 4) + 221, 368, 201, 64 },
    { (g_windowW / 4) + 427, 368, 201, 64 },
    { (g_windowW / 4) + 12, 48, 201, 64 },
    { (g_windowW / 4) + 221, 48, 201, 64 },
    { (g_windowW / 4) + 427, 48, 201, 64 },
    { (g_windowW / 4) + 224, 464, 193, 48 },
    { (g_windowW / 4) + 224, 528, 193, 64 },
    { (g_windowW / 4) + 224, 608, 193, 64 },
    { g_windowW / 4, 464, 96, 96 },
    { (g_windowW / 4) + 432, 464, 96, 96 },
    { g_windowW / 4, 464, 208, 96 },
    { (g_windowW / 4) + 432, 464, 208, 96 },
    { (g_windowW / 4) + 12, 368, 64, 64 },
    { (g_windowW / 4) + 221, 368, 64, 64 },
    { (g_windowW / 4) + 427, 368, 64, 64 },
    { (g_windowW / 4) + 12, 48, 64, 64 },
    { (g_windowW / 4) + 221, 48, 64, 64 },
    { (g_windowW / 4) + 427, 48, 64, 64 },
    { (g_windowW / 4) + 75, 368, 138, 30 },
    { (g_windowW / 4) + 284, 368, 138, 30 },
    { (g_windowW / 4) + 490, 368, 138, 30 },
    { (g_windowW / 4) + 75, 48, 138, 30 },
    { (g_windowW / 4) + 284, 48, 138, 30 },
    { (g_windowW / 4) + 490, 48, 138, 30 },
    {0, 0, 62, 62}
    

};

std::vector<SDL_Rect> rectsEn = {
    { (g_windowW / 4) + 49, 112, 128, 256 },
    { (g_windowW / 4) + 258, 112, 128, 256 },
    { (g_windowW / 4) + 464, 112, 128, 256 }
};

WMKEnemy::WMKEnemy() {

    std::uniform_int_distribution<> speedrng(0, 9); 

    for (int filter = 1; filter != 4 ; filter++) {



        std::vector<enStats> filterEn;
        
        for (int s = 0; s < listEn.size();s++) {
            if (listEn[s].threatLv < filter) {
                filterEn.push_back(listEn[s]);
            }
        }
        std::uniform_int_distribution<> bossrng(0, listEnSpecial.size()-1);

        for (int i = 0; i < 11; i++) {
            std::uniform_int_distribution<> fillrng(0, filterEn.size()-1);

            int e = fillrng(gen);
            segmentEn.push_back(filterEn[e]);
    
        }
        for (int sp = 0; sp < segmentEn.size();sp++) {
            std::uniform_int_distribution<> speednow(segmentEn[sp].speedRange[0], segmentEn[sp].speedRange[1]);
            segmentEn[sp].spdCur = speednow(gen);
        }
        segmentEn.push_back(listEnSpecial[bossrng(gen)]);
 

    }
}



WMKScreen::WMKScreen() {       
        int i = 0;
		
		std::uniform_int_distribution<> facerng(0, (faces.size()-1));
        std::uniform_int_distribution<> namerng(0x000000, 0xFFFFFF);  
        std::uniform_int_distribution<> speedrng(0, 9); 
        
		for (i; i != party.size(); i++) {            
            
            
            int f = facerng(gen);
            int n = namerng(gen);

			party[i].face = faces[f];
            party[i].name = std::vformat(" {0:6X}",std::make_format_args(n));
            for (int ispd = 0; ispd < 2; ispd++) {
               int s = speedrng(gen);
               party[i].speedRange.push_back(s);
            }
            std::sort(party[i].speedRange.begin(), party[i].speedRange.end());
            std::uniform_int_distribution<> speednow(0, party[i].speedRange[1]);
            int sc = speednow(gen);
            party[i].spdCur = sc;

            if ((party[i].speedRange[1]) < 4) {
                party[i].health = hp + party[i].speedRange[1];
            }
            else if ((party[i].speedRange[1]) > 4) {
                party[i].health = hp - party[i].speedRange[1];
            }
            else if ((party[i].speedRange[1]) == 4) {
                party[i].health = hp;
            }

		}
}


void WMKScreen::tick() {
    if (closeNextTick) {
        g_closeScreen(this);
    }
}

void WMKScreen::gameProcess() {
    
   
}



void WMKEnemy::renderEnemies() {
    int xval = 197;
    for (int i = 0; i < rectsEn.size(); i++) {

    SDL_RenderCopy(g_rd, segmentEn[i].face, NULL, &rects[25 + i]);
    SDL_RenderCopy(g_rd, segmentEn[i].combat, NULL, &rectsEn[0 + i]);
    }

    g_fnt->RenderString(segmentEn[0].name, (g_windowW / 4) + 75, 48);
    g_fnt->RenderString(segmentEn[1].name, (g_windowW / 4) + 284, 48);
    g_fnt->RenderString(segmentEn[2].name, (g_windowW / 4) + 490, 48);
    for (int i = 0; i != rectsEn.size(); i++) {
        g_fnt->RenderString(std::to_string(segmentEn[i].spdCur), (g_windowW / 4) + xval, 49);
        SDL_RenderDrawLine(g_rd,(g_windowW / 4) + 193, 48,(g_windowW / 4) + 193, 110);
        SDL_RenderDrawLine(g_rd,(g_windowW / 4) + 400, 48,(g_windowW / 4) + 400, 110);
        SDL_RenderDrawLine(g_rd,(g_windowW / 4) + 607, 48,(g_windowW / 4) + 607, 110);
        xval += 207;

    }
}

void WMKScreen::render()  {
    
    DrawBackground();

    SDL_Color colorR1 = { 0x30, 0x30, 0x30, 0xa0 };
    SDL_Color colorR2 = { 0x20, 0x20, 0x20, 0xa0 };
    SDL_Color colorR3 = { 0x10, 0x10, 0x10, 0xa0 };
    SDL_Color bkColour1 = { 0x30, 0x30, 0x30, 0xa2 };
    SDL_Color bkColour2 = { 0x20, 0x20, 0x20, 0xa2 };
    SDL_Color bkColour3 = { 0x10, 0x10, 0x10, 0xa2 };
    SDL_Color bkStat1 = { 0x20, 0x20, 0x20, 0xFF };
    SDL_Color bkStat2 = { 0x0, 0x0, 0x0, 0xFF };
    SDL_Color bkStat3 = { 0x0, 0x0, 0x0, 0xFF };

    SDL_SetRenderDrawColor(g_rd, 0xff, 0xff, 0xff, 0x80);

    for (int i = 0; i < rects.size(); i++) {
        if (i < 19) {

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
        }
        if (i != 34) {
            SDL_RenderDrawRect(g_rd, &rects[i]);
        }

    }
    

    ens.renderEnemies();
    setRandFacesAndNames();
    SDL_RenderDrawLine(g_rd,(g_windowW / 4) + 150, 368,(g_windowW / 4) + 150, 396);
    SDL_RenderDrawLine(g_rd,(g_windowW / 4) + 356, 368,(g_windowW / 4) + 356, 396);
    SDL_RenderDrawLine(g_rd,(g_windowW / 4) + 562, 368,(g_windowW / 4) + 562, 396);
    SDL_RenderCopy(g_rd, party[0].face, &rects[34], &rects[22]);
    SDL_RenderCopy(g_rd, party[1].face, &rects[34], &rects[23]);
    SDL_RenderCopy(g_rd, party[2].face, &rects[34], &rects[24]);
    g_fnt->RenderString("Combat Viewport", g_windowW/4, 8);
    g_fnt->RenderString("Combat Log", (g_windowW/4)+656, 8);
    g_fnt->RenderString("Inactive Cache", (g_windowW/4)+656, 464);
    g_fnt->RenderString("Payload Cache", 128, 8);
    g_fnt->RenderString("Run Status:", 128, 464);
    g_fnt->RenderString("RANGE(" + std::to_string(party[playerSel].speedRange[0]) + "," + std::to_string(party[playerSel].speedRange[1]) + ")", (g_windowW / 4) + 98, 464);
    g_fnt->RenderString("ARMOR(" + std::to_string(party[playerSel].health) + ")", (g_windowW / 4) + 98, 484);
}

void WMKScreen::setRandFacesAndNames() {
    //i unforgor :D
    int xval = 150; 
    SDL_RenderCopy(g_rd, party[0].face, NULL, &rects[18]);
    SDL_RenderCopy(g_rd, tex, NULL, &rects[19]);
    g_fnt->RenderString(party[0].name, (g_windowW / 4) + 75, 368);
    g_fnt->RenderString(party[1].name, (g_windowW / 4) + 284, 368);
    g_fnt->RenderString(party[2].name, (g_windowW / 4) + 490, 368);
    for (int i = 0; i != party.size(); i++) {
        g_fnt->RenderString(" SPD(" + std::to_string(party[i].spdCur) + ")", (g_windowW / 4) + xval, 368);
        xval += 207;
    }
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