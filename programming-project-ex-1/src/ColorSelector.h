#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#include <bobcat_ui/all.h>
#include "Color.h"
#include "Enums.h"

class ColorSelector : public bobcat::Group {
public:
    bobcat::Button* redButton;
    bobcat::Button* orangeButton;
    bobcat::Button* yellowButton;
    bobcat::Button* greenButton;
    bobcat::Button* blueButton;
    bobcat::Button* indigoButton;
    bobcat::Button* violetButton;


    void deselectAllColors();
    
    void onClick(bobcat::Widget* sender);

    COLOR color;
    void visualizeSelectedColor();
    ColorSelector(int x, int y, int w, int h);

    Color getColor() const;

    friend struct AppTest;
};

#endif