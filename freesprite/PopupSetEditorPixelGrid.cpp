#include "PopupSetEditorPixelGrid.h"
#include "FontRenderer.h"
#include "UIDropdown.h"

PopupSetEditorPixelGrid::PopupSetEditorPixelGrid(MainEditor* parent, std::string tt, std::string tx) 
{

    wxHeight = 280;
    std::vector<std::string> names;
    for (XY& tileSize : predefinedTileSizes) {  
        names.push_back(xyEqual(tileSize, { 0,0 }) ? std::string("No grid") : std::format("{}x{}", tileSize.x, tileSize.y));
    }

    this->caller = parent;
    this->title = tt;
    this->text = tx;
    UIButton* nbutton = new UIButton();
    nbutton->text = "Set";
    nbutton->position = XY{ wxWidth - 260, wxHeight - 40 };
    nbutton->wxWidth = 120;
    nbutton->setCallbackListener(0, this);
    wxsManager.addDrawable(nbutton);

    UIButton* nbutton2 = new UIButton();
    nbutton2->text = "Cancel";
    nbutton2->position = XY{ wxWidth - 130, wxHeight - 40 };
    nbutton2->wxWidth = 120;
    nbutton2->setCallbackListener(1, this);
    wxsManager.addDrawable(nbutton2);

    tboxX = new UITextField();
    tboxX->position = XY{ 20, 80 };
    tboxX->text = std::to_string(caller->tileDimensions.x);
    tboxX->wxWidth = 120;
    wxsManager.addDrawable(tboxX);

    tboxY = new UITextField();
    tboxY->position = XY{ 160, 80 };
    tboxY->text = std::to_string(caller->tileDimensions.y);
    tboxY->wxWidth = 120;
    wxsManager.addDrawable(tboxY);

    UILabel* paddingLabel = new UILabel();
    paddingLabel->position = XY{ 20, 125 };
    paddingLabel->text = "Padding";
    wxsManager.addDrawable(paddingLabel);


    UILabel* ll = new UILabel();
    ll->position = XY{ 120, 125 };
    ll->text = "Right";
    wxsManager.addDrawable(ll);

    tboxPadRX = new UITextField();
    tboxPadRX->position = XY{ 175, 125 };
    tboxPadRX->text = std::to_string(caller->tileGridPaddingBottomRight.x);
    tboxPadRX->wxWidth = 60;
    wxsManager.addDrawable(tboxPadRX);

    ll = new UILabel();
    ll->position = XY{ 250, 125 };
    ll->text = "Bottom";
    wxsManager.addDrawable(ll);

    tboxPadBY = new UITextField();
    tboxPadBY->position = XY{ 320, 125 };
    tboxPadBY->text = std::to_string(caller->tileGridPaddingBottomRight.y);
    tboxPadBY->wxWidth = 60;
    wxsManager.addDrawable(tboxPadBY);

    UILabel* opacityLabel = new UILabel();
    opacityLabel->position = XY{ 20, 185 };
    opacityLabel->text = "Opacity";
    wxsManager.addDrawable(opacityLabel);

    opacitySlider = new UISlider();
    opacitySlider->position = XY{100, 180};
    opacitySlider->wxHeight = 40;
    opacitySlider->sliderPos = caller->tileGridAlpha / 255.0f;
    wxsManager.addDrawable(opacitySlider);

    UIDropdown* dropdown = new UIDropdown(names);
    dropdown->position = XY{ 300, 80 }; 
    dropdown->text = "Presets";
    dropdown->setCallbackListener(39, this);
    wxsManager.addDrawable(dropdown);
}

void PopupSetEditorPixelGrid::render()
{
	renderDefaultBackground();

	XY titlePos = getDefaultTitlePosition();
	XY contentPos = getDefaultContentPosition();

	g_fnt->RenderString(title, titlePos.x, titlePos.y);
	g_fnt->RenderString(text, contentPos.x, contentPos.y);
    //XY opacityTextPos = xyAdd(getPopupOrigin(), XY{ 20, 140 });
    //g_fnt->RenderString("Opacity", opacityTextPos.x, opacityTextPos.y);
	renderDrawables();
}

