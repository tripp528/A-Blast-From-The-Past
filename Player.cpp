//
// Created by Tripp Gordon on 11/14/17.
//

#include "Player.h"


Player::Player() {
    name = "Unknown";
    score = 0;
    width = 50;
    height = 50;
    type = PLAYER;
    bullet.setDirection(Direction::right);
}

Player::Player(const Position &p,
               const LaserBullet &b, double h, string n) : AbstractCreature(p, b, h) {
    name = n;
    score = 0;
    width = 50;
    height = 50;

}

Player::~Player() {

}

string Player::getName() const{
    return name;
}

int Player::getScore() const {
    return score;
}

void Player::setName(string n){
    name = n;
}

void Player::setScore(int s) {
    score = s;
}


void Player::incrementScore(int amount) {
    setScore(score + amount);
}

void Player::draw() {


/*
 * Following texture code from:
 * arekkusu. (2007, April 3). Simple textures with GLUT? [Blog post]. Retrieved
 * from iDevGames website: http://www.idevgames.com/forums/thread-3374.html
 */
    // hardcoded RGBA values

    //4-bit per component values (16 bits per pixel) for a few rgba colors
#define TEX_INTERNAL GL_RGBA4
#define TEX_FORMAT   GL_RGBA
#define TEX_TYPE     GL_UNSIGNED_SHORT_4_4_4_4


#define R 0xf30f
#define W 0x111f
#define X 0x0000
#define G 0x5c6c
#define B 0x001F


    unsigned short player_texture [(16 * 16)] = {
            //touches left wall (back)
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,R,W,W,R,X,X,R,W,W,R,X,X,X,
            X,X,X,X,R,R,R,R,R,R,R,R,X,X,X,X,
            X,X,X,X,G,R,R,R,R,R,R,G,X,X,X,X,
            X,X,X,X,G,X,R,R,R,R,X,G,X,X,X,X,
            X,X,X,X,G,X,R,R,R,R,X,G,X,X,X,X,
            X,X,X,X,X,X,R,B,B,R,X,X,X,X,X,X,
            X,X,X,X,X,X,R,B,B,R,X,X,X,X,X,X,
            X,X,X,X,X,X,X,R,R,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,R,R,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,W,W,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,W,W,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,

            //points towards aliens (gun point)
    };




    glTexImage2D(GL_TEXTURE_2D, 0, TEX_INTERNAL, 16, 16, 0, TEX_FORMAT, TEX_TYPE, player_texture);

//disabling mipmaps for this texture to be "complete"
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

//drwaing a quad with the texture

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2i(position.xCoord, position.yCoord);//glVertex2f(16,  16);
    glTexCoord2f(1, 0); glVertex2i(position.xCoord, position.yCoord + height);//glVertex2f(0, 16);
    glTexCoord2f(1, 1); glVertex2i(position.xCoord + width, position.yCoord + height);//glVertex2f(0,0);
    glTexCoord2f(0, 1); glVertex2i(position.xCoord + width, position.yCoord);//glVertex2f(16, 0);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Player::reportScore() const {

    /*
     * append each name and score to a file
     */

    ofstream f_out("high_score.txt", ios::app);
    if (f_out) {
        f_out << name << "     \t" << score << endl;
    }
    f_out.close();
}

void Player::collide(const Object &o) {
    if(o.getType() == BULLET || o.getType() == ALIEN) {
        --healthPoints;
        if (healthPoints == 0) {
            setIsDrawn(false);
        }
    }
}