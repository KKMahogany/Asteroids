//
//  player.cpp
//  Asteroids
//
//  Created by Kevin Tran on 2/06/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#include "player.h"

Player::Player (double newXPos,
                double newYPos,
                double newRadius,
                double newXSpeed,
                double newYSpeed,
                sf::Color color) : Entity(newXPos,
                                          newYPos,
                                          newRadius,
                                          newXSpeed,
                                          newYSpeed,
                                          color) {
    weapon = Weapon();
    return;
}

Weapon* Player::getWeapon (void) {
    return &weapon;
}

void Player::setWeapon (Weapon newWeapon) {
    weapon = newWeapon;
}

void Player::selfDestruct (void) {
    sprite.setRadius(0.01f);
}

