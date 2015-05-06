//
//  entity.h
//  Asteroids
//
//  Created by Kevin Tran on 28/03/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#ifndef __Asteroids__entity__
#define __Asteroids__entity__

#include <SFML/Graphics.hpp>
#include <iostream>

class Entity {

protected:

    double xPos;
    double yPos;

    double xSpeed;
    double ySpeed;
    
    
    sf::CircleShape sprite;
    double spriteRadius;
    sf::Color spriteColor;
    
public:
    
    Entity (double newXPos,
            double newYPos,
            double newRadius,
            double newXSpeed,
            double newYSpeed,
            sf::Color color);
    
    
    double getXPos (void);
    double getYPos (void);
    double getXSpeed (void);
    double getYSpeed (void);
    
    double getRadius (void);
    
    void setSpeed (double newX, double newY);
    
    void update (double timeStep);
    
    sf::CircleShape* getSprite (void);
};

#endif /* defined(__Asteroids__entity__) */
