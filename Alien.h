//
// Created by Tripp Gordon on 11/14/17.
//

#ifndef A_BLAST_FROM_THE_PAST_BASEALIEN_H
#define A_BLAST_FROM_THE_PAST_BASEALIEN_H

#include "AbstractCreature.h"

class Alien : public AbstractCreature {
public:
    /*
     * (Constructors)
     *
     * Requires: Nothing
     * Modifies: All fields
     * Effects: Constructs an Alien
    */
    Alien();
    Alien(const Position &p, const LaserBullet &b, double h);
    ~Alien();

    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Draws the Alien
     */
    void draw() override;

    /*
     * Requires: Nothing
     * Modifies: All fields of the class
     * Effects: Deals with collision with other objects
     */
    void collide(const Object &o) override;
};


#endif //A_BLAST_FROM_THE_PAST_BASEALIEN_H
