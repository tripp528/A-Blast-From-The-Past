//
// Created by Tripp Gordon on 11/6/17.
//
#include "LaserBullet.h"


LaserBullet::LaserBullet() {
    width = 25;
    height = 15;
    isDrawn = false;
    type = BULLET;
}

//LaserBullet::LaserBullet() : Object() {
//
//}

LaserBullet::LaserBullet(const Position &p) : Object(p) {

}

LaserBullet::~LaserBullet() {

}

Direction LaserBullet::getDirection() const {
    return direction;
}

void LaserBullet::setPosition(const Position &p) {
    setPosition(p.xCoord,p.yCoord);
}

void LaserBullet::setPosition(int x, int y) {
    if (x < 0) {
        isDrawn = false;
    }
    if (y < 0) {
        isDrawn = false;
    }
    if (x + width > boardWidth) {
        isDrawn = false;
    }
    if (y + height > boardHeight) {
        isDrawn = false;
    }

    position.xCoord = x;
    position.yCoord = y;
}

void LaserBullet::setDirection(const Direction &d) {
    direction = d;
}

void LaserBullet::collide() {
    isDrawn = false;
}

void LaserBullet::draw() {

/*
 * Following texture code from:
 * arekkusu. (2007, April 3). Simple textures with GLUT? [Blog post]. Retrieved
 * from iDevGames website: http://www.idevgames.com/forums/thread-3374.html
 */
    // hardcoded RGBA values
#define X 0x0000
#define G 0x5c6c



    unsigned short laser_texture [(16 * 16)] = {
            //touches left wall (back)
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,
            G,X,X,X,X,X,X,X,X,X,X,X,X,X,X,G,

            //points towards aliens (gun point)
    };


//4-bit per component values (16 bits per pixel) for a few rgba colors
#define TEX_INTERNAL GL_RGBA4
#define TEX_FORMAT   GL_RGBA
#define TEX_TYPE     GL_UNSIGNED_SHORT_4_4_4_4

    glTexImage2D(GL_TEXTURE_2D, 0, TEX_INTERNAL, 16, 16, 0, TEX_FORMAT, TEX_TYPE, laser_texture);

//Disable mipmaps for this texture to be "complete"
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

//drawing a quad with the texture
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2i(position.xCoord, position.yCoord + 15);//glVertex2f(16,  16);
    glTexCoord2f(1, 0); glVertex2i(position.xCoord, position.yCoord + height + 15);//glVertex2f(0, 16);
    glTexCoord2f(1, 1); glVertex2i(position.xCoord + width, position.yCoord + height + 15);//glVertex2f(0,0);
    glTexCoord2f(0, 1); glVertex2i(position.xCoord + width, position.yCoord + 15);//glVertex2f(16, 0);

    glEnd();

    //disabling texture so the rest of the program will draw
    glDisable(GL_TEXTURE_2D);
}
