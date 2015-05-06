//
//  particle.h
//  Asteroids
//
//  Created by Kevin Tran on 28/05/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#ifndef __Asteroids__particle__
#define __Asteroids__particle__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "entity.h"

class Particle : public Entity {
private:
    sf::Time lifeSpan;
public:
    Particle (double newXPos,
              double newYPos,
              double newRadius,
              double newXSpeed,
              double newYSpeed,
              sf::Color color,
              double newLifeSpan);
    void update (double timeStep);
    sf::Time getLifeSpan (void);
};

#endif /* defined(__Asteroids__particle__) */
