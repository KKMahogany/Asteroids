//
//  asteroid.h
//  Asteroids
//
//  Created by Kevin Tran on 28/03/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#ifndef __Asteroids__asteroid__
#define __Asteroids__asteroid__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "entity.h"

class Asteroid : public Entity {
private:
    int size;
public:
    
    Asteroid(double newXPos,
             double newYPos,
             int newSize,
             double xSpeed,
             double ySpeed,
             double newRadius,
             sf::Color color);
    
    bool collides (double xMouse, double yMouse);
    
    int getSize (void);
    void split (void);

};

#endif /* defined(__Asteroids__asteroid__) */
