//
// Created by Tripp Gordon on 12/8/17.
//

#include "Button.h"

Button::Button() {

}

Button::~Button() {

}

Color Button::getFill() const {
    return fill;
}

void Button::setFill(const Color &f) {
    fill = f;
}

void Button::draw() {
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_QUADS);
    // top left corner
    glVertex2i(position.xCoord, position.yCoord);
    // top right corner
    glVertex2i(position.xCoord + width, position.yCoord);
    // bottom right corner
    glVertex2i(position.xCoord + width, position.yCoord + height);
    // bottom left corner
    glVertex2i(position.xCoord, position.yCoord + height);
    glEnd();
}


