//
//  weapon.cpp
//  Asteroids
//
//  Created by Kevin Tran on 2/06/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#include "weapon.h"
#include "utilityFunctions.h"

Bullet Weapon::getBullet (int index, int x, int y, double angle) {
    assert(index >= 0 && index < bulletList.size());
    Bullet newBullet(x,
                     y,
                     bulletList[index],
                     angle+bulletOffset[index]);
    return newBullet;
}

double Weapon::getFireRate (void) {
    return fireRate;
}

Weapon::Weapon (std::vector<Bullet> bullets, std::vector<double> offsets, double rate) {
    bulletList = bullets;
    bulletOffset = offsets;
    fireRate = rate;
    return;
}

Weapon::Weapon (weaponType type) :
                                    bulletList (getWeapon(type).bulletList),
                                    bulletOffset (getWeapon(type).bulletOffset),
                                    fireRate (getWeapon(type).fireRate) {}

int Weapon::getNumBullets (void) {
    return bulletList.size();
}

