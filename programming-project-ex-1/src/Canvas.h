#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/all.h>
#include <vector>
#include "Enums.h"
#include "Scribble.h"

class Canvas : public bobcat::Canvas_ {
public:
    std::vector<Scribble*> scribbles;
    std::vector<bobcat::Button*> sneakyButtons;
    

    Canvas(int x, int y, int w, int h);

    void addScribble(float x, float y, float r, float g, float b, std::string type, int size=7, float base=0, float height=0, float width=0, float length=0, int sides=0, float radius=0.0, std::vector<Point *> points = std::vector<Point*>());
    void removeScribble(int index);

    void clear();

    void render(); 
};

#endif