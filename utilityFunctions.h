//
//  utilityFunctions.h
//  Asteroids
//
//  Created by Kevin Tran on 31/05/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#ifndef __Asteroids_utilityFunctions_h
#define __Asteroids_utilityFunctions_h

#include "constants.h"
#include "weapon.h"

inline double getRandomDir (int fineness = STANDARD_ANGLE_FINENESS) {
    assert(fineness > 0);
    return (2.0f*PI)*(static_cast<double>(rand()%1000)/static_cast<double>(fineness));
}

inline double getExplosionParticleLifeSpan (int size) {
    return EXPLOSION_PARTICLE_LIFESPAN + (size-1)*0.5f;
}

inline double getExplosionParticleSpeed (int size) {
    return EXPLOSION_PARTICLE_SPEED + (size-1)*20;
}

inline Weapon getWeapon (weaponType weapon) {
    std::vector<Bullet> bulletList;
    std::vector<double> offsetList;
    double fireRate;

    switch (weapon) {
        case SPREAD_SHOT:
            fireRate = FIRE_RATE*3;
            for(int i = 0; i < 3; i++) {
                bulletList.push_back(Bullet(0,
                                            0,
                                            PROJECTILE_RADIUS,
                                            PROJECTILE_SPEED,
                                            PROJECTILE_SPEED,
                                            PROJECTILE_COLOR));
            }
            offsetList.push_back(-PI/8.0f);
            offsetList.push_back(0.0f);
            offsetList.push_back(PI/8.0f);
            break;
        case CHAIN_GUN:
            fireRate = FIRE_RATE;
            bulletList.push_back(Bullet(0,
                                        0,
                                        PROJECTILE_RADIUS,
                                        PROJECTILE_SPEED,
                                        PROJECTILE_SPEED,
                                        PROJECTILE_COLOR));
            offsetList.push_back(0);
            break;
        case MINE_LAYER:
            fireRate = FIRE_RATE*2;
            bulletList.push_back(Bullet(0,
                                        0,
                                        PROJECTILE_RADIUS*4,
                                        0,
                                        0,
                                        PROJECTILE_COLOR));
            offsetList.push_back(0);
            break;
        case SPLINTER_GUN:
            for(int i = 0; i < 12; i++) {
                bulletList.push_back(Bullet(0,
                                            0,
                                            PROJECTILE_RADIUS,
                                            PROJECTILE_SPEED,
                                            PROJECTILE_SPEED,
                                            PROJECTILE_COLOR));
                offsetList.push_back(static_cast<double>(i)*(2.0f*PI/12.0f));
            }
            fireRate = FIRE_RATE*8;
            break;
        case CANNON:
            for(int i = 0; i < 5; i++) {
                bulletList.push_back(Bullet(0,
                                            0,
                                            PROJECTILE_RADIUS*6,
                                            PROJECTILE_SPEED*0.5f,
                                            PROJECTILE_SPEED*0.5f,
                                            PROJECTILE_COLOR));
                offsetList.push_back(0.0f);
            }
            fireRate = FIRE_RATE*7;
            break;
    }
    
    return Weapon(bulletList, offsetList, fireRate);
}

#endif
