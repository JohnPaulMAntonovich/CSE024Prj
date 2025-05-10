#include "Application.h"
#include "Point.h"
#include <cmath>

//using namespace bobcat;
using namespace std;

bool sketching = false;
vector<Point*> points;
int position = 0;
Scribble *selected = NULL;

void Application::onCanvasMouseDown(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL) {
        sketching = true;
        points.push_back(new Point(mx, my));
        canvas->addScribble(mx, my, color.getR(), color.getG(), color.getB(), "sketch", 7, 0, 0, 0, 0, 0, 0, points);
        canvas->redraw();
    }
    else if (tool == SELECT) {
        for (size_t i = 0; i < canvas->scribbles.size(); ++i) {
            if (canvas->scribbles[i]->type == "sketch") {
                for (size_t x = 0; x < canvas->scribbles[i]->points.size(); ++x) {
                    if(abs(mx - canvas->scribbles[i]->points[x]->getX()) <= 0.01*canvas->scribbles[i]->size)
                        if(abs(my - canvas->scribbles[i]->points[x]->getY()) <= 0.01*canvas->scribbles[i]->size) {
                            selected = canvas->scribbles[i];  position = i;}}
            } else if (canvas->scribbles[i]->type == "circle") {
                float rad = canvas->scribbles[i]->radius;
                if (abs(mx - canvas->scribbles[i]->x) <= 1*rad)
                    if (abs(my - canvas->scribbles[i]->y) <= 1*rad) {
                        selected = canvas->scribbles[i];  position = i;}
            } else if (canvas->scribbles[i]->type == "rectangle") {
                if (abs(mx - canvas->scribbles[i]->x) <= 1*canvas->scribbles[i]->width)
                    if (abs(my - canvas->scribbles[i]->y) <= 1*canvas->scribbles[i]->height) {
                        selected = canvas->scribbles[i];  position = i;}
            } else if (canvas->scribbles[i]->type == "triangle") {
                if (abs(mx - canvas->scribbles[i]->x) <= 1*canvas->scribbles[i]->base)
                    if (abs(my - canvas->scribbles[i]->y) <= 1*canvas->scribbles[i]->height) {
                        selected = canvas->scribbles[i];  position = i;  }
            }  else if (canvas->scribbles[i]->type == "polygon") {
                if (abs(mx - canvas->scribbles[i]->x) <= 1*canvas->scribbles[i]->length)
                    if (abs(my - canvas->scribbles[i]->y) <= 1*canvas->scribbles[i]->length) {
                        selected = canvas->scribbles[i]; position = i;}
            }
        }

        if (selected != NULL) {
            toolbar->eraserButton->color(FL_BACKGROUND_COLOR);
            toolbar->sizeUpButton->color(FL_BACKGROUND_COLOR);
            toolbar->sizeDownButton->color(FL_BACKGROUND_COLOR);
            toolbar->bringFrontButton->color(FL_BACKGROUND_COLOR);
            toolbar->putBackButton->color(FL_BACKGROUND_COLOR);
        }

    }
    else if (tool == CIRCLE) {
        canvas->addScribble(mx, my, color.getR(),
            color.getG(), color.getB(), "circle",
            0, 0, 0, 0, 0, 0, 0.1);
        canvas->redraw();
    }
    else if (tool == TRIANGLE) {
        canvas->addScribble(mx, my, color.getR(),
            color.getG(), color.getB(), "triangle",
            0, 0.2, 0.2);
        canvas->redraw();
    }
    else if (tool == RECTANGLE) {
        canvas->addScribble(mx, my, color.getR(),
            color.getG(), color.getB(), "rectangle",
            0, 0, 0.2, 0.2);
        canvas->redraw();
    }
    else if (tool == POLYGON) {
        canvas->addScribble(mx, my, color.getR(),
            color.getG(), color.getB(), "polygon",
            0, 0, 0, 0, 0.1, 6);
        canvas->redraw();
    }
}

void Application::onCanvasDrag(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL && sketching == true) {
        canvas->scribbles[0]->points.push_back(new Point(mx, my));
        canvas->redraw();
    } if (tool == SELECT && selected != NULL) {
        canvas->scribbles[position]->x = mx;
        canvas->scribbles[position]->y = my;
        canvas->redraw();
    }
}


void Application::onCanvasMouseUp(bobcat::Widget* sender, float mx, float my) {
    if (toolbar->getTool() == PENCIL) {
        canvas->scribbles[0]->points.push_back(new Point(mx, my));
        canvas->redraw();
        sketching = false;
        points.clear();
    }
}


void Application::onToolbarChange(bobcat::Widget* sender) {
    ACTION action = toolbar->getAction();

    if (action == CLEAR) {
        selected = NULL;
        canvas->clear();
        canvas->redraw();
    } else if (action == ERASE && selected != NULL) {
        std::cout << "ran";
        canvas->scribbles.erase(canvas->scribbles.begin() + position);
        canvas->redraw();
        selected = NULL;
        position = 0;
    } else if (action == SIZEUP && selected != NULL) {
        std::string type = canvas->scribbles[position]->type;

        if (type == "sketch")
            canvas->scribbles[position]->size += 1;
        else if (type == "circle")
            canvas->scribbles[position]->radius += 0.1;
        else if (type == "rectangle") {
            canvas->scribbles[position]->width += 0.1; canvas->scribbles[position]->height += 0.1; }
        else if (type == "polygon") {
            canvas->scribbles[position]->length += 0.1;}
        else if (type == "triangle") {
            canvas->scribbles[position]->base += 0.1; canvas->scribbles[position]->height += 0.1; }
    }  else if (action == SIZEDOWN && selected != NULL) {
        std::string type = canvas->scribbles[position]->type;

        if (type == "sketch" && canvas->scribbles[position]->size > 1)
            canvas->scribbles[position]->size -= 1;
        else if (type == "circle" && canvas->scribbles[position]->radius > 0.2)
            canvas->scribbles[position]->radius -= 0.1;
        else if (type == "rectangle" && canvas->scribbles[position]->width > 0.2 && canvas->scribbles[position]->height > 0.2) {
            canvas->scribbles[position]->width -= 0.1; canvas->scribbles[position]->height -= 0.1; }
        else if (type == "polygon" && canvas->scribbles[position]->length > 0.2) {
            canvas->scribbles[position]->length -= 0.1;}
        else if (type == "triangle" && canvas->scribbles[position]->base > 0.2 && canvas->scribbles[position]->height > 0.2) {
            canvas->scribbles[position]->base -= 0.1; canvas->scribbles[position]->height -= 0.1; }
    }  else if (action == BRINGFRONT && selected != NULL) {
        Scribble *temp = canvas->scribbles[position];
        canvas->scribbles.erase(canvas->scribbles.begin() + position);
        canvas->scribbles.insert(canvas->scribbles.begin(), temp);
    }  else if (action == PUTBACK && selected != NULL) {
        Scribble *temp = canvas->scribbles[position];
        canvas->scribbles.erase(canvas->scribbles.begin() + position);
        canvas->scribbles.push_back(temp);
    }

    canvas->redraw();
}

void Application::onColorChange(bobcat::Widget* sender) {
    if (selected != NULL) {
        Color newColor = colorSelector->getColor();
        selected->r = newColor.getR();
        selected->g = newColor.getG();
        selected->b = newColor.getB();
        canvas->redraw();
    }
}

Application::Application() {
    window = new bobcat::Window(100, 100, 600, 400, "Paint Application");

    toolbar = new Toolbar(0, 0, 600, 50);
    canvas = new Canvas(50, 50, 600, 350);
    colorSelector = new ColorSelector(0, 50, 50, 600);
    
    window->add(colorSelector);
    window->add(toolbar);
    window->add(canvas);


    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_MOUSE_UP(canvas, Application::onCanvasMouseUp);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    ON_CHANGE(toolbar, Application::onColorChange);
    window->show();
}