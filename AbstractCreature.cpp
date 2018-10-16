//
// Created by Tripp Gordon on 11/13/17.
//

#include "AbstractCreature.h"

AbstractCreature::AbstractCreature() {
    LaserBullet b;
    bullet = b;
    healthPoints = 1;
}

AbstractCreature::AbstractCreature(const Position &p,
                                   const LaserBullet &b, double h) : Object(p) {
    bullet = b;
    healthPoints = h;
}

AbstractCreature::~AbstractCreature() {}

LaserBullet AbstractCreature::getBullet() const {
    return bullet;
}

double AbstractCreature::getHealthPoints() const {
    return healthPoints;
}

void AbstractCreature::setBullet(const LaserBullet &b) {
    bullet = b;
}

void AbstractCreature::setHealthPoints(double h) {
    healthPoints = h;
}

void AbstractCreature::shoot() {
    bullet.setPosition(position);
    bullet.setIsDrawn(true);
}

void AbstractCreature::moveBullet() {
    bullet.move(10,0);
}

void AbstractCreature::drawBullet() {
    bullet.draw();
}
