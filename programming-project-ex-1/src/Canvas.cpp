#include "Canvas.h"
#include <GL/freeglut.h>

Canvas::Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h) {
    // 
}

void Canvas::addScribble(float x, float y, float r, float g, float b, std::string type, int size, float base, float height, float width, float length, int sides, float radius, std::vector<Point*> points) {
    scribbles.insert(scribbles.begin(), new Scribble( x,  y,  r,  g,  b, type,  size,  base,  height,  width,  length,  sides,  radius, points));
}

void Canvas::clear() {
    for (size_t i = 0; i < scribbles.size(); ++i)
        delete scribbles[i];
    
    scribbles.clear();
}

void Canvas::render() {
    for (size_t i = 0; i < scribbles.size(); ++i)
        scribbles[i]->draw();
}