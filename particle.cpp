//
//  particle.cpp
//  Asteroids
//
//  Created by Kevin Tran on 28/05/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#include "constants.h"
#include "particle.h"

Particle::Particle (double newXPos,
                    double newYPos,
                    double newRadius,
                    double newXSpeed,
                    double newYSpeed,
                    sf::Color color,
                    double newLifeSpan) : Entity(newXPos,
                                              newYPos,
                                              newRadius,
                                              newXSpeed,
                                              newYSpeed,
                                              color) {
    lifeSpan = sf::seconds(newLifeSpan);
};

sf::Time Particle::getLifeSpan (void) {
    return lifeSpan;
}


void Particle::update (double timeStep) {
    xPos += timeStep*xSpeed;
    yPos += timeStep*ySpeed;
    if(xPos < -getRadius()) {
        xPos = SCREEN_WIDTH + getRadius() - EPSILON;
    }
    if(xPos > SCREEN_WIDTH + getRadius()) {
        xPos = -getRadius() + EPSILON;
    }
    if(yPos < -getRadius()) {
        yPos = SCREEN_HEIGHT + getRadius() - EPSILON;
    }
    if(yPos > SCREEN_HEIGHT + getRadius()) {
        yPos = -getRadius() + EPSILON;
    }
    lifeSpan -= sf::seconds(timeStep);
    return;
}