//
//  constants.h
//  Asteroids
//
//  Created by Kevin Tran on 4/05/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#ifndef Asteroids_constants_h
#define Asteroids_constants_h
#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>

#include "ResourcePath.hpp"

const int STANDARD_ANGLE_FINENESS = 1000;
const int MAX_PARTICLES = 200;

const double EPSILON = 0.0000001f;
const double PI = 3.14159265358f;

const double PLAYER_ACCELERATION = 800.0f;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const double FIRE_RATE = 0.1f;

const double PROJECTILE_RADIUS = 6.0f;
const double PROJECTILE_SPEED = 400.0f;
const double PLAYER_RADIUS = 20.0f;

const double MAX_PLAYER_SPEED = 300.0f;
const sf::Color PLAYER_COLOR = sf::Color(220, 124, 38);
const sf::Color ASTEROID_COLOR = sf::Color(100, 10, 240);
const sf::Color PROJECTILE_COLOR = sf::Color(255, 255, 40);

const double EXPLOSION_PARTICLE_SPEED = 80.0f;
const double EXPLOSION_PARTICLE_RADIUS = 3.0f;
const double PARTICLES_PER_EXPLOSION[4] = {-1, 3, 6, 12};
const sf::Color EXPLOSION_PARTICLE_COLOR = sf::Color(128, 128, 128);
const double EXPLOSION_PARTICLE_LIFESPAN = 0.6f;

const double ASTEROID_RADIUS[4] = {-1.0f, 15.0f, 30.0f, 80.0f}; // One based
const double ASTEROID_SPEED[4] = {-1.0f, 120.0f, 80.0f, 40.0f};

enum weaponType {
    SPREAD_SHOT,
    CHAIN_GUN,
    SPLINTER_GUN,
    MINE_LAYER,
    CANNON,
};

enum powerUpType {
    EXPLOSION,
    RAPID_FIRE,
    SLOW_TIME,
    INVINCIBLE,
};

const double ROUND_TEXT_DURATION = 1.0f;

#endif
