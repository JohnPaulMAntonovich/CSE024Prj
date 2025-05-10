#include "Toolbar.h"
using namespace bobcat;

void Toolbar::deselectAllTools() {
    selectButton->color(FL_BACKGROUND_COLOR);
    pencilButton->color(FL_BACKGROUND_COLOR);
    circleButton->color(FL_BACKGROUND_COLOR);
    triangleButton->color(FL_BACKGROUND_COLOR);
    rectangleButton->color(FL_BACKGROUND_COLOR);
    polygonButton->color(FL_BACKGROUND_COLOR);
    //eraserButton->color(FL_BACKGROUND_COLOR);
    // sizeUpButton->color(FL_BACKGROUND_COLOR);
    // sizeDownButton->color(FL_BACKGROUND_COLOR);
    // bringFrontButton->color(FL_BACKGROUND_COLOR);
    // putBackButton->color(FL_BACKGROUND_COLOR);
    
}

void Toolbar::visualizeSelectedTool() {
    if (tool == SELECT) {
        selectButton->color(FL_WHITE);
    }
    else if (tool == PENCIL) {
        pencilButton->color(FL_WHITE);
    }
    else if (tool == CIRCLE) {
        circleButton->color(FL_WHITE);
    }
    else if (tool == TRIANGLE) {
        triangleButton->color(FL_WHITE);
    }
    else if (tool == RECTANGLE) {
        rectangleButton->color(FL_WHITE);
    }
    else if (tool == POLYGON) {
        polygonButton->color(FL_WHITE);
    }
}

void Toolbar::onClick(bobcat::Widget* sender) {
    deselectAllTools();
    action = NONE;

    if (sender == selectButton) {
        tool = SELECT;
    }
    else if (sender == pencilButton) {
        tool = PENCIL;
    }
    else if (sender == circleButton) {
        tool = CIRCLE;
    }
    else if (sender == triangleButton) {
        tool = TRIANGLE;
    }
    else if (sender == rectangleButton) {
        tool = RECTANGLE;
    }
    else if (sender == polygonButton) {
        tool = POLYGON;
    }
    else if (sender == eraserButton)
        action = ERASE;
    else if (sender == clearButton) {
        action = CLEAR;
    } else if (sender == sizeUpButton) {
        action = SIZEUP;
    } else if (sender == sizeDownButton) {
        action = SIZEDOWN;
    } else if (sender == bringFrontButton) {
        action = BRINGFRONT;
    } else if (sender == putBackButton) {
        action = PUTBACK;
    }

    if (onChangeCb) {
        onChangeCb(this);
    }

    visualizeSelectedTool();
    redraw();
}

TOOL Toolbar::getTool() const {
    return tool;
}

ACTION Toolbar::getAction() const {
    return action;
}

Toolbar::Toolbar(int x, int y, int w, int h) : Group(x, y, w, h) {
    selectButton = new Image(x, y, 50, 50, "./assets/mouse.png");
    pencilButton = new Image(x + 50, y, 50, 50, "./assets/pencil.png");
    eraserButton = new Image(x + 100, y, 50, 50, "./assets/eraser.png");
    circleButton = new Image(x + 150, y, 50, 50, "./assets/circle.png");
    triangleButton = new Image(x + 200, y, 50, 50, "./assets/triangle.png");
    rectangleButton = new Image(x + 250, y, 50, 50, "./assets/rectangle.png");
    polygonButton = new Image(x + 300, y, 50, 50, "./assets/polygon.png");
    clearButton = new Image(x + 350, y, 50, 50, "./assets/clear.png");
    sizeUpButton = new Image(x + 400, y, 50, 50, "./assets/plus.png");
    sizeDownButton = new Image(x + 450, y, 50, 50, "./assets/minus.png");
    bringFrontButton = new Image(x + 500, y, 50, 50, "./assets/bring-to-front.png");
    putBackButton = new Image(x + 550, y, 50, 50, "./assets/send-to-back.png");

    tool = PENCIL;
    action = NONE;

    selectButton->box(FL_BORDER_BOX);
    pencilButton->box(FL_BORDER_BOX);
    eraserButton->box(FL_BORDER_BOX);
    circleButton->box(FL_BORDER_BOX);
    triangleButton->box(FL_BORDER_BOX);
    rectangleButton->box(FL_BORDER_BOX);
    polygonButton->box(FL_BORDER_BOX);
    clearButton->box(FL_BORDER_BOX);
    sizeUpButton->box(FL_BORDER_BOX);
    sizeDownButton->box(FL_BORDER_BOX);
    bringFrontButton->box(FL_BORDER_BOX);
    putBackButton->box(FL_BORDER_BOX);

    eraserButton->color(FL_INACTIVE_COLOR);
    sizeDownButton->color(FL_INACTIVE_COLOR);
    bringFrontButton->color(FL_INACTIVE_COLOR);
    putBackButton->color(FL_INACTIVE_COLOR);
    sizeUpButton->color(FL_INACTIVE_COLOR);

    visualizeSelectedTool();

    ON_CLICK(selectButton, Toolbar::onClick);
    ON_CLICK(pencilButton, Toolbar::onClick);
    ON_CLICK(eraserButton, Toolbar::onClick);
    ON_CLICK(circleButton, Toolbar::onClick);
    ON_CLICK(triangleButton, Toolbar::onClick);
    ON_CLICK(rectangleButton, Toolbar::onClick);
    ON_CLICK(polygonButton, Toolbar::onClick);
    ON_CLICK(clearButton, Toolbar::onClick);
    ON_CLICK(sizeUpButton, Toolbar::onClick);
    ON_CLICK(sizeDownButton, Toolbar::onClick);
    ON_CLICK(bringFrontButton, Toolbar::onClick);
    ON_CLICK(putBackButton, Toolbar::onClick);
}