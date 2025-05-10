#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>
#include "Canvas.h"
#include "Toolbar.h"
#include "Color.h"
#include "ColorSelector.h"

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    Toolbar* toolbar;
    ColorSelector* colorSelector;
    Canvas* canvas;

    void onCanvasMouseDown(bobcat::Widget* sender, float mx, float my);
    void onCanvasDrag(bobcat::Widget* sender, float mx, float my);
    void onToolbarChange(bobcat::Widget* sender);
    void onCanvasMouseUp(bobcat::Widget* sender, float mx, float my);
    void onColorChange(bobcat::Widget* sender);

public:
    Application();

    friend struct::AppTest;
};


#endif