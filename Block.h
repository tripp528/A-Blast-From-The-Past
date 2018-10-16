//
// Created by Tripp Gordon on 11/29/17.
//

#ifndef A_BLAST_FROM_THE_PAST_BLOCK_H
#define A_BLAST_FROM_THE_PAST_BLOCK_H

#include "LaserBullet.h"

class Block : public Object {
private:
    int healthPoints;
public:
    /*
     * (Constructors)
     *
     * Requires: Nothing
     * Modifies: The speed field and direction field
     * Effects: Constructs a LaserBullet
     */
    Block();
    Block(const Position &p);
    ~Block() override;

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns Returns fields of the class
     */
    int getHealthPoints() const;

    /*
     * Requires: Nothing
     * Modifies: all fields of the class
     * Effects: Set all fields of the class
     */
    void setHealthPoints(int h);

    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Draws the block
     */
    void draw() override;

    /*
     * Requires: Nothing
     * Modifies: All fields of the class
     * Effects: Deals with collision with other objects
     */
    void collide(const Object &o) override;

};


#endif //A_BLAST_FROM_THE_PAST_BLOCK_H
