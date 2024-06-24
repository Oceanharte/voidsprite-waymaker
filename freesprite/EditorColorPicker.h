#pragma once
#include "drawable.h"
#include "DrawableManager.h"
#include "EventCallbackListener.h"
#include "UIHueSlider.h"
#include "UIColorSlider.h"
#include "UISVPicker.h"
#include "UITextField.h"
#include "UIButton.h"
#include "TabbedView.h"

class EditorColorPicker : public Drawable, public EventCallbackListener
{
public:
	int wxWidth = 400;
	int wxHeight = 380;
	MainEditor* caller;

	DrawableManager subWidgets;

	double currentH = 0, currentS = 0, currentV = 0;

	uint8_t currentR = 0, currentG = 0, currentB = 0;

	UIHueSlider* hueSlider;
	UISVPicker* satValSlider;
	UITextField* colorTextField;
	UISlider* sliderH;
	UIColorSlider* sliderS;
	UIColorSlider* sliderV;
	UIColorSlider* sliderR;
	UIColorSlider* sliderG;
	UIColorSlider* sliderB;
	TabbedView* tbv;

	UIButton* eraserButton;

	EditorColorPicker(MainEditor* c) {
		caller = c;
		tbv = new TabbedView({{"Visual", g_iconColorVisual}, {"HSV", g_iconColorHSV}, {"RGB", g_iconColorRGB}}, 90);
		tbv->position = XY{ 20,30 };
		subWidgets.addDrawable(tbv);

		hueSlider = new UIHueSlider(this);
		hueSlider->position = XY{0,0};
		tbv->tabs[0].wxs.addDrawable(hueSlider);

		satValSlider = new UISVPicker(this);
		satValSlider->position = XY{ 0,70 };
		tbv->tabs[0].wxs.addDrawable(satValSlider);

		sliderH = new UISlider();
		sliderH->position = XY{ 70, 10 };
		sliderH->wxWidth = 200;
		sliderH->setCallbackListener(EVENT_COLORPICKER_SLIDERH, this);
		tbv->tabs[1].wxs.addDrawable(sliderH);	

		sliderS = new UIColorSlider();
		sliderS->position = XY{ 70, 60 };
		sliderS->wxWidth = 200;
		sliderS->setCallbackListener(EVENT_COLORPICKER_SLIDERS, this);
		tbv->tabs[1].wxs.addDrawable(sliderS);		
		
		sliderV = new UIColorSlider();
		sliderV->position = XY{ 70, 110 };
		sliderV->wxWidth = 200;
		sliderV->setCallbackListener(EVENT_COLORPICKER_SLIDERV, this);
		tbv->tabs[1].wxs.addDrawable(sliderV);

		sliderR = new UIColorSlider();
		sliderR->position = XY{ 70, 10 };
		sliderR->wxWidth = 200;
		sliderR->setCallbackListener(EVENT_COLORPICKER_SLIDERR, this);
		tbv->tabs[2].wxs.addDrawable(sliderR);

		sliderG = new UIColorSlider();
		sliderG->position = XY{ 70, 60 };
		sliderG->wxWidth = 200;
		sliderG->setCallbackListener(EVENT_COLORPICKER_SLIDERG, this);
		tbv->tabs[2].wxs.addDrawable(sliderG);

		sliderB = new UIColorSlider();
		sliderB->position = XY{ 70, 110 };
		sliderB->wxWidth = 200;
		sliderB->setCallbackListener(EVENT_COLORPICKER_SLIDERB, this);
		tbv->tabs[2].wxs.addDrawable(sliderB);

		colorTextField = new UITextField();
		colorTextField->color = true;
		colorTextField->position = XY{ 60, 340 };
		colorTextField->wxWidth = 140;
		colorTextField->setCallbackListener(EVENT_COLORPICKER_TEXTFIELD, this);
		subWidgets.addDrawable(colorTextField);

		eraserButton = new UIButton();
		eraserButton->position = { 20, 340 };
		//eraserButton->text = "E";
		eraserButton->icon = g_iconEraser;
		eraserButton->wxWidth = 30;
		eraserButton->setCallbackListener(EVENT_COLORPICKER_TOGGLEERASER, this);
		subWidgets.addDrawable(eraserButton);
	}

	bool isMouseIn(XY thisPositionOnScreen, XY mousePos) override;
	void render(XY position) override;
	void handleInput(SDL_Event evt, XY gPosOffset) override;
	void focusOut() override {
		Drawable::focusOut();
		subWidgets.forceUnfocus();
	}
	void eventTextInput(int evt_id, std::string data) override;
	void eventTextInputConfirm(int evt_id, std::string data) override;
	void eventButtonPressed(int evt_id) override;
	void eventSliderPosChanged(int evt_id, float f) override;

	void toggleEraser();
	void updateMainEditorColor();
	void updateMainEditorColorFromRGBSliders();
	void setMainEditorColorRGB(unsigned int col);
	void setMainEditorColorRGB(SDL_Color col, bool updateHSVSliders = true, bool updateRGBSliders = true);

	void editorColorHSliderChanged(double h) {
		currentH = h;
		updateMainEditorColor();
	}
	void editorColorSVPickerChanged(double s, double v) {
		currentS = s;
		currentV = v;
		updateMainEditorColor();
	}
};

