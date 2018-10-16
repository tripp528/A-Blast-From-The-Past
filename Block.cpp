//
// Created by Tripp Gordon on 11/29/17.
//

#include "Block.h"


Block::Block() {
    healthPoints = 50;
    width = healthPoints;
    height = healthPoints*2;
    type = BLOCK;
}

Block::Block(const Position &p) : Object(p) {
    width = 50;
    height = 100;
}

Block::~Block() {

}

int Block::getHealthPoints() const {
    return healthPoints;
}

void Block::setHealthPoints(int h) {
    healthPoints = h;
}

void Block::draw() {

    //glColor3f(fill.red, fill.green, fill.blue);
    glColor3f(1, 1, 1);
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



    unsigned short alien_texture [(16 * 16)] = {
            //touches left wall (back)
            X,R,X,R,X,R,X,R,X,R,X,R,X,R,X,R,
            R,X,R,X,R,X,R,X,R,X,R,X,R,X,R,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,R,X,R,X,R,X,R,X,R,X,R,X,R,X,R,
            R,X,R,X,R,X,R,X,R,X,R,X,R,X,R,X,

            //points towards aliens (gun point)
    };




    glTexImage2D(GL_TEXTURE_2D, 0, TEX_INTERNAL, 16, 16, 0, TEX_FORMAT, TEX_TYPE, alien_texture);

//disabling mipmapsfor this texture to be "complete"
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

// drawing a quad with the texture
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2i(position.xCoord, position.yCoord);//glVertex2f(16,  16);
    glTexCoord2f(1, 0); glVertex2i(position.xCoord, position.yCoord + height);//glVertex2f(0, 16);
    glTexCoord2f(1, 1); glVertex2i(position.xCoord + width, position.yCoord + height);//glVertex2f(0,0);
    glTexCoord2f(0, 1); glVertex2i(position.xCoord + width, position.yCoord);//glVertex2f(16, 0);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Block::collide(const Object &o) {
    if(o.getType() == BULLET) {
        --healthPoints;
        width = healthPoints;
        height = healthPoints*2;
        if (healthPoints < 2) {
            healthPoints = 0;
            setIsDrawn(false);
        }
    }
}


