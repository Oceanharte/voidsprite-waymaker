#pragma once
#include "globals.h"
#include "BaseScreen.h"
#include "DrawableManager.h"
#include "EditorColorPicker.h"
#include "EditorLayerPicker.h"
#include "BaseBrush.h"
#include "Brush1x1.h"
#include "Brush3pxCircle.h"
#include "Brush1pxLine.h"
#include "BrushRect.h"
#include "BrushRectFill.h"
#include "ToolRectClone.h"
#include "ToolColorPicker.h"
#include "ToolSetXSymmetry.h"
#include "ToolSetYSymmetry.h"
#include "Layer.h"
#include "SpritesheetPreviewScreen.h"
#include "ToolComment.h"
#include "ToolMeasure.h"

struct CommentData {
	XY position;
	std::string data;
	Timer64 animTimer;
	bool hovered = false;
};

class MainEditor : public BaseScreen, public EventCallbackListener
{
public:
	SpritesheetPreviewScreen* spritesheetPreview = NULL;

	std::vector<CommentData> comments;

	std::vector<Layer*> layers;
	int selLayer = 0;

	int maxUndoHistory = 20;
	std::vector<UndoStackElement> undoStack, redoStack;

	int texW = -1, texH = -1;
	XY tileDimensions = XY{ 0,0 };
	uint8_t tileGridAlpha = 0x40;
	XY canvasCenterPoint = XY{0,0};
	XY mousePixelTargetPoint;
	XY mousePixelTargetPoint2xP;
	int scale = 1;
	XY mouseHoldPosition;
	bool closeNextTick = false;
	BaseBrush* currentBrush = new Brush1x1();
	bool leftMouseHold = false;
	bool middleMouseHold = false;

	bool changesSinceLastSave = false;
	PlatformNativePathString lastConfirmedSavePath;
	int lastConfirmedExporterId;
	bool lastConfirmedSave = false;

	bool eraserMode = false;
	uint32_t pickedColor = 0xFFFFFF;

	GlobalNavBar* navbar;
	DrawableManager wxsManager;
	EditorColorPicker* colorPicker;
	EditorBrushPicker* brushPicker;
	EditorLayerPicker* layerPicker;

	SDL_Color backgroundColor = SDL_Color{0,0,0,255};

	XY symmetryPositions = {0,0};
	bool symmetryEnabled[2] = { false, false };

	MainEditor(XY dimensions);
	MainEditor(SDL_Surface* srf);
	MainEditor(Layer* srf);
	MainEditor(std::vector<Layer*> layers);
	~MainEditor();

	void render() override;
	void tick() override;
	void takeInput(SDL_Event evt) override;

	std::string getName() override { return "Editor"; }

	void eventFileSaved(int evt_id, PlatformNativePathString name, int exporterId) override;
	void eventPopupClosed(int evt_id, BasePopup* p) override;
	void eventTextInputConfirm(int evt_id, std::string text) override;
	
	void DrawBackground();
	void DrawForeground();
	void renderComments();
	void drawSymmetryLines();
	void initLayers();
	void SetUpWidgets();
	void RecalcMousePixelTargetPoint(int x, int y);
	void FillTexture();
	void SetPixel(XY position, uint32_t color, uint8_t symmetry = 0);
	void DrawLine(XY from, XY to, uint32_t color);
	void trySaveImage();
	void trySaveAsImage();
	void recenterCanvas();
	bool requestSafeClose();
	void zoom(int how_much);
	bool isInBounds(XY pos);

	void checkAndDiscardEndOfUndoStack();
	void commitStateToLayer(Layer* l);
	void commitStateToCurrentLayer();
	void addToUndoStack(UndoStackElement undo);
	void discardRedoStack();
	void undo();
	void redo();

	Layer* newLayer();
	void deleteLayer(int index);
	void moveLayerUp(int index);
	void moveLayerDown(int index);
	void mergeLayerDown(int index);
	Layer* getCurrentLayer() {
		return layers[selLayer];
	}
	void layer_flipHorizontally();
	void layer_flipVertically();
	void layer_swapLayerRGBtoBGR();
	uint32_t layer_getPixelAt(XY pos);
	Layer* flattenImage();
	Layer* mergeLayers(Layer* bottom, Layer* top);

	bool canAddCommentAt(XY a);
	void addCommentAt(XY a, std::string c);
	void removeCommentAt(XY a);
private:
	CommentData _removeCommentAt(XY a);
};

