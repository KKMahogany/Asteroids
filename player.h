//
//  player.h
//  Asteroids
//
//  Created by Kevin Tran on 2/06/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#ifndef __Asteroids__player__
#define __Asteroids__player__

#include "constants.h"
#include "weapon.h"

class Player : public Entity {
private:
    Weapon weapon;
public:
    Player (double newXPos,
            double newYPos,
            double newRadius,
            double newXSpeed,
            double newYSpeed,
            sf::Color color);
    
    Weapon* getWeapon (void);
    void selfDestruct (void);
    void setWeapon (Weapon newWeapon);
};

#endif /* defined(__Asteroids__player__) */
