//
// Created by Tripp Gordon on 11/13/17.
//

#ifndef A_BLAST_FROM_THE_PAST_ABSTRACTCREATURE_H
#define A_BLAST_FROM_THE_PAST_ABSTRACTCREATURE_H

#include "LaserBullet.h"

/*
 * Description: Abstract class to govern all aliens and players
 */
class AbstractCreature : public Object {
protected:
    LaserBullet bullet;
    double healthPoints;
public:
    /*
     * (Constructors)
     *
     * Requires: Nothing
     * Modifies: All fields
     * Effects: Constructs an AbstractCreature
    */
    AbstractCreature();

    AbstractCreature(const Position &p, const LaserBullet &b, double h);

    virtual ~AbstractCreature();

    /*
     * (Getters)
     *
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns the values of all fields
     */
    virtual LaserBullet getBullet() const;

    virtual double getHealthPoints() const;

    /*
     * (Setters)
     *
     * Requires: Nothing
     * Modifies: The values of all fields
     * Effects: Set the values of all fields
     */
    virtual void setBullet(const LaserBullet &b);

    virtual void setHealthPoints(double h);

    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Shoots a LaserBullet
     */
    void shoot();

    /*
     * Requires: Nothing
     * Modifies: Position field of bullet
     * Effects: Calls setPosition to change the position of the object
     */
    void moveBullet();

    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Draws a LaserBullet
     */
    void drawBullet();

};

#endif //A_BLAST_FROM_THE_PAST_ABSTRACTCREATURE_H
