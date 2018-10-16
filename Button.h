//
// Created by Tripp Gordon on 12/8/17.
//

#ifndef A_BLAST_FROM_THE_PAST_BUTTON_H
#define A_BLAST_FROM_THE_PAST_BUTTON_H

#include "Object.h"

class Button : public Object {
private:
    Color fill;
public:
    /*
     * (Constructors)
     *
     * Requires: Nothing
     * Modifies: The speed field and direction field
     * Effects: Constructs a LaserBullet
     */
    Button();
    ~Button() override;

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns Returns fields of the class
     */
    Color getFill() const;

    /*
     * Requires: Nothing
     * Modifies: all fields of the class
     * Effects: Set all fields of the class
     */
    void setFill(const Color &f);

    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Draws the block
     */
    void draw() override;

};


#endif //A_BLAST_FROM_THE_PAST_BUTTON_H
