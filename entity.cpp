//
//  entity.cpp
//  Asteroids
//
//  Created by Kevin Tran on 28/03/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//


#include "entity.h"
#include "constants.h"

Entity::Entity (double newXPos,
                double newYPos,
                double newRadius,
                double newSpeedX,
                double newSpeedY,
                sf::Color color) {
    
    xPos = newXPos;
    yPos = newYPos;
    spriteRadius = newRadius;
    
    assert (newRadius > 0.00001f);
    
    spriteColor = color;
    
    setSpeed (newSpeedX,newSpeedY);
    
    return;
}

double Entity::getXPos (void) {
    return xPos;
}

double Entity::getYPos (void) {
    return yPos;
}

sf::CircleShape *Entity::getSprite (void) {
    sprite.setFillColor(spriteColor);
    sprite.setPosition(xPos-spriteRadius, yPos-spriteRadius);
    sprite.setRadius(spriteRadius);
    return &sprite;
}


double Entity::getXSpeed (void) {
    return xSpeed;
}

double Entity::getYSpeed (void) {
    return ySpeed;
}

void Entity::update (double timeStep) {
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
    return;
}

void Entity::setSpeed (double newX, double newY) {
    xSpeed = newX;
    ySpeed = newY;
}

double Entity::getRadius (void) {
    return spriteRadius;
}
