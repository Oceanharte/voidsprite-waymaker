#pragma once
#include "globals.h"
#include "BaseScreen.h"
#include "Notification.h"
#include "UITextField.h"
#include "UIButton.h"
#include "PopupMessageBox.h"
#include "EventCallbackListener.h"

class WMKScreen : public BaseScreen, public EventCallbackListener
{
public:
	bool closeNextTick = false;
	SDL_Texture* tex;
	SDL_Color backgroundColor = SDL_Color{0,0,0,255};

	void render() override;
	void tick() override;
	void takeInput(SDL_Event) override;

	std::string getName() override { return "voidsprite :: waymaker"; }
	void renderBackground();
	void DrawBackground();
};