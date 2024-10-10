#pragma once
#include "globals.h"
#include "BaseBrush.h"

//test pattern get rid of this later thanks
inline int segXLine1 = 6, segXLine2 = 6;	// |  |
inline int segYLine1 = 6, segYLine2 = 6;   // _  _
inline u32 patternPixels[] = {
0x00000000,0x00000000,0x00000000,0x00000000,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x00000000,0xFF9A9A9A,0xFF9A9A9A,0xFF1E1E1E,0xFF000000,0xFF393939,0xFF393939,0xFF393939,0xFF393939,0xFF393939,0xFF393939,0xFF000000,0xFF1E1E1E,0xFF9A9A9A,0xFF9A9A9A,0x00000000,0x00000000,
0x00000000,0xFF9A9A9A,0xFF1E1E1E,0xFF1E1E1E,0xFF393939,0xFF000000,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFF000000,0xFF393939,0xFF1E1E1E,0xFF1E1E1E,0xFF9A9A9A,0x00000000,
0x00000000,0xFF9A9A9A,0xFF393939,0xFF393939,0xFF393939,0xFF000000,0xFFCCCCCC,0xFFCCCCCC,0xFFA3A3A3,0xFFA3A3A3,0xFFCCCCCC,0xFFCCCCCC,0xFF000000,0xFF393939,0xFF393939,0xFF393939,0xFF9A9A9A,0x00000000,
0xFF9A9A9A,0xFF393939,0xFF393939,0xFFCCCCCC,0xFFCCCCCC,0xFF000000,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFF000000,0xFFCCCCCC,0xFFCCCCCC,0xFF393939,0xFF393939,0xFF9A9A9A,
0xFF9A9A9A,0xFF000000,0xFF000000,0xFF000000,0xFF000000,0xFF000000,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFF000000,0xFF000000,0xFF000000,0xFF000000,0xFF000000,0xFF9A9A9A,
0xFF9A9A9A,0xFF393939,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFF393939,0xFF9A9A9A,
0xFF9A9A9A,0xFF393939,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFF393939,0xFF9A9A9A,
0xFF9A9A9A,0xFF393939,0xFFCCCCCC,0xFFA3A3A3,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFA3A3A3,0xFFCCCCCC,0xFF393939,0xFF9A9A9A,
0xFF9A9A9A,0xFF393939,0xFFCCCCCC,0xFFA3A3A3,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFA3A3A3,0xFFCCCCCC,0xFF393939,0xFF9A9A9A,
0xFF9A9A9A,0xFF393939,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFF393939,0xFF9A9A9A,
0xFF9A9A9A,0xFF393939,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFF393939,0xFF9A9A9A,
0xFF9A9A9A,0xFF000000,0xFF000000,0xFF000000,0xFF000000,0xFF000000,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFF000000,0xFF000000,0xFF000000,0xFF000000,0xFF000000,0xFF9A9A9A,
0xFF9A9A9A,0xFF393939,0xFF393939,0xFFCCCCCC,0xFFCCCCCC,0xFF000000,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFF000000,0xFFCCCCCC,0xFFCCCCCC,0xFF393939,0xFF393939,0xFF9A9A9A,
0x00000000,0xFF9A9A9A,0xFF393939,0xFF393939,0xFF393939,0xFF000000,0xFFCCCCCC,0xFFCCCCCC,0xFFA3A3A3,0xFFA3A3A3,0xFFCCCCCC,0xFFCCCCCC,0xFF000000,0xFF393939,0xFF393939,0xFF393939,0xFF9A9A9A,0x00000000,
0x00000000,0xFF9A9A9A,0xFF1E1E1E,0xFF1E1E1E,0xFF393939,0xFF000000,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFFCCCCCC,0xFF000000,0xFF393939,0xFF1E1E1E,0xFF1E1E1E,0xFF9A9A9A,0x00000000,
0x00000000,0x00000000,0xFF9A9A9A,0xFF9A9A9A,0xFF1E1E1E,0xFF000000,0xFF393939,0xFF393939,0xFF393939,0xFF393939,0xFF393939,0xFF393939,0xFF000000,0xFF1E1E1E,0xFF9A9A9A,0xFF9A9A9A,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00000000,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0xFF9A9A9A,0x00000000,0x00000000,0x00000000,0x00000000,
};
inline XY fullPatternDims = { 18, 18 };

class Brush9SegmentRect :
    public BaseBrush
{
    XY startPos = XY{ 0,0 };
    bool heldDown = false;
    XY lastMousePos = XY{ 0,0 };

    void resetState() {
        startPos = XY{ 0,0 };
    }
    std::string getName() override { return "9-segment Rectangle [WIP]"; };
    std::string getTooltip() override { return "Mouse Right to select a 9-segment pattern.\nSelect a rectangle with Mouse Left to place it."; }
    std::string getIconPath() override { return VOIDSPRITE_ASSETS_PATH "assets/brush_9srect.png"; }
    bool overrideRightClick() override { return true; }
    void clickPress(MainEditor* editor, XY pos) override;
    void clickDrag(MainEditor* editor, XY from, XY to) override { lastMousePos = to; }
    void clickRelease(MainEditor* editor, XY pos) override;
    void rightClickPress(MainEditor* editor, XY pos) override;
    void renderOnCanvas(XY canvasDrawPoint, int scale) override;
};

