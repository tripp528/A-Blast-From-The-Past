////
// Created by Tripp Gordon on 11/14/17.
//

#ifndef A_BLAST_FROM_THE_PAST_PLAYER_H
#define A_BLAST_FROM_THE_PAST_PLAYER_H

#include "AbstractCreature.h"
#include <fstream>
#include "Block.h"



class Player : public AbstractCreature {

private:
    string name;
    int score;
public:
    /*
     * (Constructors)
     *
     * Requires: Nothing
     * Modifies: All fields
     * Effects: Constructs a Player
    */
    Player();
    Player(const Position &p, const LaserBullet &b, double h, string n);


    ~Player() override;

    /*
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns Returns fields of the class
     */
    string getName() const;
    int getScore() const;

    /*
     * Requires: Nothing
     * Modifies: all fields of the class
     * Effects: Set all fields of the class
     */
    void setName(string n);
    void setScore(int s);
    void incrementScore(int amount);



    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Draws the player
     */
    void draw() override;

    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Writes your score to our high_Score file
     * @param i
     */
    void reportScore() const;

    /*
     * Requires: Nothing
     * Modifies: All fields of the class
     * Effects: Deals with collision with other objects
     */
    void collide(const Object &o) override;

};


#endif //A_BLAST_FROM_THE_PAST_PLAYER_H