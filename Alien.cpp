//
// Created by Tripp Gordon on 11/14/17.
//

#include "Alien.h"


Alien::Alien() {
    type = ALIEN;
    healthPoints = 1;
    bullet.setDirection(Direction ::left);
}

Alien::Alien(const Position &p,
             const LaserBullet &b, double h) : AbstractCreature(p, b, h) {

}

Alien::~Alien() {

}

void Alien::draw() {
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
#define P 0x1a8b


    unsigned short alien_texture [(16 * 16)] = {
            //touches left wall (back)
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,G,G,X,X,X,X,X,X,X,
            X,X,X,X,X,X,G,G,G,G,X,X,X,X,X,X,
            X,X,X,X,X,G,G,R,R,G,G,X,X,X,X,X,
            X,X,X,X,X,G,G,R,R,G,G,X,X,X,X,X,
            X,X,X,X,G,G,G,G,G,G,G,G,X,X,X,X,
            X,X,X,G,G,G,G,G,G,G,G,G,G,X,X,X,
            X,X,G,G,G,G,G,G,G,G,G,G,G,G,X,X,
            X,G,G,G,G,G,G,G,G,G,G,G,G,G,G,X,
            G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,G,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
            X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,

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



void Alien::collide(const Object &o) {
    if(o.getType() == BULLET) {
        --healthPoints;
        if (healthPoints == 0) {
            setIsDrawn(false);
        }
    }
}