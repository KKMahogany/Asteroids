//
//  asteroid.cpp
//  Asteroids
//
//  Created by Kevin Tran on 28/03/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#include "asteroid.h"
#include <iostream>
Asteroid::Asteroid(double newXPos,
                   double newYPos,
                   int newSize,
                   double newXSpeed,
                   double newYSpeed,
                   double newRadius,
                   sf::Color newColor)
: Entity(newXPos,newYPos,newRadius,newXSpeed,newYSpeed, newColor), size(newSize) {}

int Asteroid::getSize (void) {
    return size;
}

bool Asteroid::collides (double xMouse, double yMouse) {
    return (abs(getXPos()-xMouse) < getRadius() &&
            abs(getYPos()-yMouse) < getRadius());
}
