#pragma once
#include "globals.h"
#include "BaseScreen.h"
#include "Notification.h"
#include "UITextField.h"
#include "UIButton.h"
#include "PopupMessageBox.h"
#include "EventCallbackListener.h"

struct plrStats {
	int health;
	SDL_Texture* face;
	std::string name;
	std::vector<int> speedRange;
	//skills vector
	//passives vector
	
};

class WMKPlayer : public BaseScreen, public EventCallbackListener
{
public:

	bool closeNextTick = false;
	SDL_Texture* tex;
	SDL_Color backgroundColor = SDL_Color{0,0,0,255};

	void render() override;
};