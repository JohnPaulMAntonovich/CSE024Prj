#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include <string>
#include <vector>
#include "Point.h"

class Scribble {
public:
    float x;
    float y;
    float r;
    float g;
    float b;
    float base;
    float height;
    float width;
    float length;
    int size;
    int sides;
    float radius;
    std::string type;
    std::vector<Point*> points;

    Scribble(float x, float y, float r, float g, float b, std::string type, int size=7, float base=0, float height=0, float width=0, float length=0, int sides=0, float radius=0.0, std::vector<Point *> points = std::vector<Point*>());

    int getX();
    int getY();
    int getR();
    int getG();
    int getB();
    void resize();
    void changeColor(float r, float g, float b);

    void draw() const;
};

#endif