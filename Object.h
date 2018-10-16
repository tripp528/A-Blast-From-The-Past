//
// Created by Tripp Gordon on 11/14/17.
//

#ifndef A_BLAST_FROM_THE_PAST_OBJECT_H
#define A_BLAST_FROM_THE_PAST_OBJECT_H

#include <iostream>
#include "graphics.h"

using namespace std;

struct Color {
    double red;
    double green;
    double blue;
};

struct Position {
    int xCoord;
    int yCoord;
};

enum Type {PLAYER, BLOCK, BULLET, ALIEN};

/**
 * Useful global variables
 */

const Color yellow = {1,1,0};
const Color white = {.9,.9,.9};
const Color purple = {.8,.7,.9};
const Position origin = {0,0};
const double boardWidth = 500;
const double boardHeight = 500;

class Object {
protected:
    Position position;
    int width;
    int height;
    Type type;
    bool isDrawn;
public:
    /*
     * (Constructors)
     *
     * Requires:
     * Modifies:
     * Effects: Constructs an object. Cannot be called unless by a derivation.
     */
    Object();
    Object(const Position &p);
    virtual ~Object();

    /*
     * (Getters)
     *
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns the values of the position and fill
     */
    virtual Position getPosition() const;
    virtual int getX() const;
    virtual int getY() const;
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual Type getType() const;
    virtual bool getIsDrawn() const;

    /*
     * (Setters)
     *
     * Requires: Nothing
     * Modifies: The values of fill and position
     * Effects: Set the values of all fields
     */
    virtual void setPosition(const Position &p);
    virtual void setPosition(int x, int y);
    virtual void setWidth(int w);
    virtual void setHeight(int h);
    virtual void setIsDrawn(bool d);

    /*
     * Requires: Nothing
     * Modifies: Position field
     * Effects: Calls setPosition to change the position of the object
     */
    virtual void move(int xChange, int yChange);

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Draws the object
     */
    virtual void draw() = 0;

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Checks to see if an object overlaps with a position
     */
    virtual bool isOverlapping(int x, int y);
    virtual bool isOverlapping(const Position &p);
    virtual bool isOverlapping(const Object &o);

    /*
     * Requires: Nothing
     * Modifies: All fields of the class
     * Effects: Deals with collision with other objects
     */
    virtual void collide(const Object &o);

};


#endif //A_BLAST_FROM_THE_PAST_OBJECT_H
