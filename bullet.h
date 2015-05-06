//
//  bullet.h
//  Asteroids
//
//  Created by Kevin Tran on 31/05/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#ifndef __Asteroids__bullet__
#define __Asteroids__bullet__

#include "entity.h"
#include "constants.h"

class Bullet : public Entity {
public:
    Bullet (double newXPos,
            double newYPos,
            double newRadius,
            double newXSpeed,
            double newYSpeed,
            sf::Color color);
    Bullet (int x,
            int y,
            Bullet bullet,
            double angle);
    void update (double timestep);
    bool outOfBounds (void);
};

#endif /* defined(__Asteroids__bullet__) */
