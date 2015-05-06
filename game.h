//
//  game.h
//  Asteroids
//
//  Created by Kevin Tran on 28/03/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#ifndef __Asteroids__game__
#define __Asteroids__game__

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "asteroid.h"
#include "particle.h"
#include "bullet.h"
#include "player.h"
#include "constants.h"
#include "utilityFunctions.h"

class Game {
private:
    sf::RenderWindow window;
    std::vector<Asteroid> asteroidList;
    std::vector<Bullet> bulletList;
    std::vector<Particle> particleList;
    
    double weaponCoolDownTime;
    
    double rapidFireTime;
    double invincibleTime;
    double slowDownTime;
    
    sf::Clock roundTime;
    Player player;
    
    int roundNum;
    
    bool gameOver;
    
public:
    Game (void);
    
    void startNextRound (void);
    bool isGameOver (void);
    
    void setPlayerWeapon (Weapon weapon);
    
    sf::RenderWindow* getWindow (void);
    void drawAsteroids (void);
    void drawPlayers (void);
    void drawBullets (void);
    void drawParticles (void);
    
    void drawScene (void);
    void update (double timeStep);
    void acceleratePlayer (double accelX, double accelY, double timeStep);
    
    void checkCollision (void);
    bool asteroidHitsPlayer (Asteroid *asteroid);
    bool projectileHits (Asteroid *asteroid, Bullet *bullet);
    
    
    void createBullet (Bullet *newBullet);
    void destroyBullet (std::vector<Bullet>::iterator it);

    void createAsteroid (int asteroidSize, double xPos, double yPos, bool edgeOfScreen = false);
    void destroyAsteroid (std::vector<Asteroid>::iterator it);
    void splitAsteroid (std::vector<Asteroid>::iterator asteroidToSplit);
    
    void createExplosion (int particles, double x, double y, int size);
    void destroyParticle (std::vector<Particle>::iterator it);
    void fire (double mouseX, double mouseY, double timeStep);
    
    void activatePowerUp (powerUpType power);
    
    void reset (void);

};

#endif /* defined(__Asteroids__game__) */
