#include "Scribble.h"
#include <GL/freeglut.h>
#include <cmath>

Scribble::Scribble(float x, float y, float r, float b, float g, std::string type, int size, float base, float height, float width, float length, int sides, float radius, std::vector<Point *> points) {
    this->x = x;
    this->y = y;
    this->r = r;
    this-> b = b;
    this->g = g;
    this->size = size;
    this->type = type;
    this->base = base;
    this->height = height;
    this->width = width;
    this->sides = sides;
    this->length = length;
    this->radius = radius;
    this->points = points;
}

void Scribble::draw() const {
    glColor3f(r, g, b);

    if (type == "sketch") {
        glPointSize(size);
        for (size_t i = 0; i < points.size(); ++i) {
            glBegin(GL_POINTS);
                glVertex2f(points[i]->getX(), points[i]->getY());
            glEnd();
        }
    } else if (type == "triangle") {
        glBegin(GL_POLYGON);
            glVertex2f(x - base/2, y - height/2);
            glVertex2f(x, y + height/2);
            glVertex2f(x + base/2, y - height/2);
        glEnd();
    } else if (type == "rectangle") {
        glColor3f(r, g, b);

        glBegin(GL_POLYGON);
            glVertex2f(x - width/2, y + height/2);
            glVertex2f(x + width/2, y + height/2);
            glVertex2f(x + width/2, y - height/2);
            glVertex2f(x - width/2, y - height/2);
        glEnd();
    } else if (type == "polygon") {
        glBegin(GL_POLYGON);
        float inc = 2 * M_PI / sides;
        for (float theta = 0; theta <= 2 * M_PI; theta += inc) {
            glVertex2f(x + length * cos(theta), y + length * sin(theta));
        }
        glEnd();
    } else if (type == "circle") {
        glBegin(GL_POLYGON);
        float inc = 2 * M_PI / 60;
        for (float theta = 0; theta <= 2 * M_PI; theta += inc) {
            glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
        }
        glEnd();
    }
}

