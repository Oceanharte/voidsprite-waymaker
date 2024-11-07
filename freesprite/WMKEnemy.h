#pragma once
#include "globals.h"
#include "BaseScreen.h"
#include "Notification.h"
#include "UITextField.h"
#include "UIButton.h"
#include "PopupMessageBox.h"
#include "EventCallbackListener.h"


struct enStats {
	int health;
	SDL_Texture* face;
	SDL_Texture* combat;
	std::string name;
	std::vector<int> speedRange;
	int spdCur;
	int threatLv;
	int role;
	//elite modifier vector
	//skills vector
	//passives vector
	
};


class WMKEnemy : public BaseScreen, public EventCallbackListener
{
public:
	
	
	bool closeNextTick = false;
	SDL_Texture* vfc = IMGLoadToTexture(VOIDSPRITE_ASSETS_PATH "assets/cface/vfc.png");
	SDL_Texture* voider = IMGLoadToTexture(VOIDSPRITE_ASSETS_PATH "assets/combatant/wmk_voider.png");
    SDL_Texture* undfc = IMGLoadToTexture(VOIDSPRITE_ASSETS_PATH "assets/cface/undfc.png");
    SDL_Texture* undostruct = IMGLoadToTexture(VOIDSPRITE_ASSETS_PATH "assets/combatant/wmk_undo.png");
    SDL_Texture* arcfc = IMGLoadToTexture(VOIDSPRITE_ASSETS_PATH "assets/cface/arcfc.png");
	SDL_Texture* arcstruct = IMGLoadToTexture(VOIDSPRITE_ASSETS_PATH "assets/combatant/wmk_arcstruct.png");



	//role memo:
	//1 = tank
	//2 = support
	//3 = attack
	SDL_Color backgroundColor = SDL_Color{0,0,0,255};

	enStats en_voider = { 25,vfc,voider," Voider",{2,4},0,0,1};
	enStats en_undostruct = { 15,undfc,undostruct," Undoform",{2,5},0,0,2 };
	enStats en_arcstruct = { 18,arcfc,arcstruct," Arcform",{1,6},0,0,3 };

	enStats en_voiderEVIL = { 99,vfc,voider," Voider-E",{2,4},0,1,1};
	enStats en_undostructEVIL = { 99,undfc,undostruct," Undoform-E",{2,5},0,1,2 };
	enStats en_arcstructEVIL = { 99,arcfc,arcstruct," Arcform-E",{1,6},0,1,3 };
	//^^^ TEMP

	//normal enemies
	std::vector<enStats> listEn = {
		en_voider,
		en_undostruct,
		en_arcstruct
	};
	//bosses
	std::vector<enStats> listEnSpecial = {
		en_voiderEVIL,
		en_undostructEVIL,
		en_arcstructEVIL
	};
	std::vector<enStats> segmentEn;
	void renderEnemies();
	WMKEnemy();
};