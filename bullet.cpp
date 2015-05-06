//
//  bullet.cpp
//  Asteroids
//
//  Created by Kevin Tran on 31/05/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#include "constants.h"
#include "bullet.h"


Bullet::Bullet (double newXPos,
        double newYPos,
        double newRadius,
        double newXSpeed,
        double newYSpeed,
        sf::Color color) : Entity(newXPos,
                                  newYPos,
                                  newRadius,
                                  newXSpeed,
                                  newYSpeed,
                                  color) {};

Bullet::Bullet (int x,
                int y,
                Bullet bullet,
                double angle) : Entity (x,
                                        y,
                                        bullet.getRadius(),
                                        bullet.getXSpeed()*cos(angle),
                                        bullet.getYSpeed()*sin(angle),
                                        bullet.getSprite()->getFillColor()) {}
void Bullet::update (double timeStep) {
    xPos += timeStep*xSpeed;
    yPos += timeStep*ySpeed;
    return;
}

bool Bullet::outOfBounds () {
    return xPos < -spriteRadius ||
           xPos > SCREEN_WIDTH + spriteRadius ||
           yPos < -spriteRadius ||
           yPos > SCREEN_HEIGHT + spriteRadius;
}