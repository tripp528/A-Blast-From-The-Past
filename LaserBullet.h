//
// Created by Tripp Gordon on 11/6/17.
//

#ifndef A_BLAST_FROM_THE_PAST_LASERBULLET_H
#define A_BLAST_FROM_THE_PAST_LASERBULLET_H


#include "Object.h"

enum Direction {up, down, left, right};

class LaserBullet : public Object {
private:
    Direction direction;
public:
    /*
     * (Constructors)
     *
     * Requires: Nothing
     * Modifies: The speed field and direction field
     * Effects: Constructs a LaserBullet
     */
    LaserBullet();
    LaserBullet(const Position &p);
    ~LaserBullet() override;

    /*
     * (Getters)
     *
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns the values of all fields
     */
    Direction getDirection() const;

    /*
     * Requires: Nothing
     * Modifies: all fields
     * Effects: Set all fields of the class
     */
    void setPosition(const Position &p) override;
    void setPosition(int x, int y) override;
    void setDirection(const Direction &d);

    /*
     * Requires: Nothing
     * Modifies: All fields of the class
     * Effects: Deals with collision with other objects
     */
    virtual void collide();

    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Draws a LaserBullet
     */
    void draw() override;


};

#endif //A_BLAST_FROM_THE_PAST_LASERBULLET_H