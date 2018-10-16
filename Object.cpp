//
// Created by Tripp Gordon on 11/14/17.
//

#include "Object.h"

Object::Object() {
    position.xCoord = 0;
    position.yCoord = 0;
    width = 0;
    height = 0;
    isDrawn = true;
}



Object::Object( const Position &p) {
    position = p;
}

Object::~Object() {

}



Position Object::getPosition() const {
    return position;
}

int Object::getX() const {
    return position.xCoord;
}

int Object::getY() const {
    return position.yCoord;
}

int Object::getWidth() const {
    return width;
}

int Object::getHeight() const {
    return height;
}

Type Object::getType() const {
    return type;
}

bool Object::getIsDrawn() const {
    return isDrawn;
}


void Object::setPosition(const Position &p) {
    setPosition(p.xCoord,p.yCoord);
}

void Object::setPosition(int x, int y) {
    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }
    if (x + width > boardWidth) {
        x = boardWidth - width;
    }
    if (y + height > boardHeight) {
        y = boardHeight - height;
    }

    position.xCoord = x;
    position.yCoord = y;
}

void Object::setWidth(int w) {
    if (w < 10) {
        w = 10;
    }
    width = w;
}

void Object::setHeight(int h) {
    if (h < 10) {
        h = 10;
    }
    height = h;
}

void Object::setIsDrawn(bool d) {
    isDrawn = d;
}

void Object::move(int xChange, int yChange) {
    setPosition(position.xCoord + xChange, position.yCoord + yChange);
}

bool Object::isOverlapping(int x, int y) {
    return (x >= position.xCoord && x <= (position.xCoord + width) &&
            y >= position.yCoord && y <= (position.yCoord + height));
}

bool Object::isOverlapping(const Position &p) {
    return isOverlapping(p.xCoord,p.yCoord);
}

bool Object::isOverlapping(const Object &o) {
    if (position.xCoord > o.position.xCoord+o.width) {
        // this is to the right of r
        return false;
    }
    if (o.position.xCoord > position.xCoord+width) {
        // r is to the right of this
        return false;
    }
    if (position.yCoord > o.position.yCoord+o.height) {
        // this is under r
        return false;
    }
    if (o.position.yCoord > position.yCoord+height) {
        // r is under this
        return false;
    }
    return true;
}



void Object::collide(const Object &o) {

}



