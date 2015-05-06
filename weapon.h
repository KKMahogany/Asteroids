//
//  weapon.h
//  Asteroids
//
//  Created by Kevin Tran on 2/06/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#ifndef __Asteroids__weapon__
#define __Asteroids__weapon__

#include "constants.h"
#include "bullet.h"
#include <vector>

class Weapon {
private:
    std::vector<Bullet> bulletList;
    std::vector<double> bulletOffset;
    double fireRate;
public:
    Weapon (weaponType type = CHAIN_GUN);
    Weapon (std::vector<Bullet> bullets, std::vector<double> offset, double rate);
    
    
    int getNumBullets (void);
    double getFireRate (void);
    Bullet getBullet (int index, int x, int y, double angle);
};

#endif /* defined(__Asteroids__weapon__) */
