#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <bobcat_ui/all.h>
#include "Enums.h"


class Toolbar : public bobcat::Group {
    public:
    bobcat::Image* selectButton;
    bobcat::Image* pencilButton;
    bobcat::Image* eraserButton;
    bobcat::Image* circleButton;
    bobcat::Image* triangleButton;
    bobcat::Image* rectangleButton;
    bobcat::Image* polygonButton;
    bobcat::Image* clearButton;

    bobcat::Image* sizeUpButton;
    bobcat::Image* sizeDownButton;
    bobcat::Image* bringFrontButton;
    bobcat::Image* putBackButton;

    TOOL tool;
    ACTION action;
    void deselectAllTools();
    void visualizeSelectedTool();
    void onClick(bobcat::Widget* sender);

    Toolbar(int x, int y, int w, int h);
    TOOL getTool() const;
    ACTION getAction() const;

};

#endif