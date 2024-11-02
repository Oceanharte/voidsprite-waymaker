#pragma once
#include "globals.h"
#include "BaseScreen.h"
#include "Notification.h"
#include "UITextField.h"
#include "UIButton.h"
#include "PopupMessageBox.h"
#include "EventCallbackListener.h"
#include <random>
#include "WMKPlayer.h"

class WMKScreen : public BaseScreen, public EventCallbackListener
{
public:

	bool closeNextTick = false;
	SDL_Color backgroundColor = SDL_Color{0,0,0,255};
    SDL_Texture* tex = IMGLoadToTexture(VOIDSPRITE_ASSETS_PATH "assets/player/nosel.png");
    SDL_Texture* teth = IMGLoadToTexture(VOIDSPRITE_ASSETS_PATH "assets/player/teth.png");
    SDL_Texture* machi = IMGLoadToTexture(VOIDSPRITE_ASSETS_PATH "assets/player/machi.png");
    SDL_Texture* gritty = IMGLoadToTexture(VOIDSPRITE_ASSETS_PATH "assets/player/gritty.png");
    SDL_Texture* furline = IMGLoadToTexture(VOIDSPRITE_ASSETS_PATH "assets/player/furline.png");

	std::vector<SDL_Texture*>faces = {
		teth,
		machi,
		gritty,
		furline
	};
	void setRandFaces();
	void render() override;
	void tick() override;
	void takeInput(SDL_Event) override;

	std::string getName() override { return "voidsprite :: waymaker"; }
	void renderBackground();
	void DrawBackground();
	WMKScreen();
};