//
//  game.cpp
//  Asteroids
//
//  Created by Kevin Tran on 28/03/14.
//  Copyright (c) 2014 Kevin Tran. All rights reserved.
//

#include "game.h"
Game::Game (void) : window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"Asteroids!"),
                    gameOver(false),
                    roundNum(0),
                    rapidFireTime(0),
                    invincibleTime(0),
                    slowDownTime(0),
                    weaponCoolDownTime(0.0f),
                    asteroidList(),
                    bulletList(),
                    player(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, PLAYER_RADIUS, 0, 0, PLAYER_COLOR) {}

sf::RenderWindow *Game::getWindow (void) {
    return &window;
}


void Game::startNextRound (void) {
    roundTime.restart();
    roundNum++;
    for(int i = 0; i < roundNum*roundNum+3; i++) {
        createAsteroid(3, rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT, true);
    }
    return;
}

bool Game::isGameOver (void) {
    return gameOver;
}

void Game::drawScene (void) {
    drawParticles();
    drawAsteroids();
    drawBullets();
    drawPlayers();
    if(gameOver) {
        sf::Font font;
        font.loadFromFile(resourcePath() + "font.ttf");

        sf::Text message("Game Over", font);
        message.setCharacterSize(135);
        message.setPosition((SCREEN_WIDTH - message.getGlobalBounds().width)/2,
                            (SCREEN_HEIGHT - message.getGlobalBounds().height*2)/2);
        message.setColor(sf::Color::Red);
        window.draw(message);
        
    }
    if(!gameOver && roundTime.getElapsedTime().asSeconds() < ROUND_TEXT_DURATION) {
        sf::Font font;
        font.loadFromFile(resourcePath() + "font.ttf");
        char roundNumAsText[3];
        std::sprintf(roundNumAsText, "%d", roundNum);
        sf::Text message("Round " + std::string(roundNumAsText), font);
        message.setCharacterSize(60);
        message.setPosition((SCREEN_WIDTH - message.getGlobalBounds().width)/2,
                            (SCREEN_HEIGHT - message.getGlobalBounds().height*2)/2);
        message.setColor(sf::Color::White);
        window.draw(message);
    }
    return;
}

void Game::setPlayerWeapon (Weapon weapon) {
    player.setWeapon(weapon);
    return;
}



void Game::drawAsteroids (void) {
    for(std::vector<Asteroid>::iterator it = asteroidList.begin();
        it != asteroidList.end(); it++) {
        window.draw(*(it->getSprite()));
    }
    return;
}

void Game::drawBullets (void) {
    for(std::vector<Bullet>::iterator it = bulletList.begin();
        it != bulletList.end(); it++) {
        window.draw(*(it->getSprite()));
    }
}

void Game::drawPlayers (void) {
    window.draw(*(player.getSprite()));
    return;
}

void Game::drawParticles (void) {
    for(std::vector<Particle>::iterator it = particleList.begin();
        it != particleList.end(); it++) {
        window.draw(*(it->getSprite()));
    }
}

void Game::update (double timeStep) {
    double adjustedTime = timeStep;
    if(slowDownTime > EPSILON) {
        slowDownTime -= timeStep;
        adjustedTime /= 10.0f;
    }
    if(rapidFireTime > EPSILON) {
        rapidFireTime -= adjustedTime;
    }
    if(invincibleTime > EPSILON) {
        invincibleTime -= adjustedTime;
    }
    if(asteroidList.size() == 0) {
        startNextRound();
    }
    if(weaponCoolDownTime > EPSILON) {
        weaponCoolDownTime -= adjustedTime;
    }
    for(std::vector<Asteroid>::iterator it = asteroidList.begin();
        it != asteroidList.end(); it++) {
        it->update(adjustedTime);
    }
    for(int i = 0; i < bulletList.size(); i++) {
        bulletList[i].update(adjustedTime);
        if(bulletList[i].outOfBounds()) {
            destroyBullet(bulletList.begin()+i);
            i--;
        }
    }
    for(int i = 0; i < particleList.size(); i++) {
        particleList[i].update(adjustedTime);
        if(particleList[i].getLifeSpan().asSeconds() < 0) {
            destroyParticle(particleList.begin()+i);;
            i--;
        }
    }
    player.update(adjustedTime);
    return;
}

void Game::acceleratePlayer (double accelX, double accelY, double timeStep) {
    
    double newXSpeed = player.getXSpeed();
    double newYSpeed = player.getYSpeed();
    
    if(!gameOver) {
        newXSpeed += accelX*timeStep;
        newYSpeed += accelY*timeStep;
        // Automatically slowdown if not accelerating
        if(accelX == 0 && accelY == 0) {
            newXSpeed *= pow(0.2f, timeStep);
            newYSpeed *= pow(0.2f, timeStep);
        }
        newXSpeed = std::min(newXSpeed, MAX_PLAYER_SPEED);
        newYSpeed = std::min(newYSpeed, MAX_PLAYER_SPEED);
        newXSpeed = std::max(newXSpeed, -MAX_PLAYER_SPEED);
        newYSpeed = std::max(newYSpeed, -MAX_PLAYER_SPEED);
        
        player.setSpeed(newXSpeed, newYSpeed);
    } else {
        // Grind to a halt fast
        if(accelX == 0 && accelY == 0) {
            newXSpeed *= pow(0.08f, timeStep);
            newYSpeed *= pow(0.08f, timeStep);
        }
        player.setSpeed(newXSpeed, newYSpeed);
    }
    return;
}


void Game::createAsteroid (int asteroidSize, double xPos, double yPos, bool edgeOfScreen) {
    int spawnSize = asteroidSize;
    double spawnX = xPos;
    double spawnY = yPos;

    double speed = ASTEROID_SPEED[asteroidSize];
    double dir = getRandomDir();
    double radius = ASTEROID_RADIUS[asteroidSize];
    if(edgeOfScreen) {
        int spawnSide = rand()%4;
        // We want a certain 90 degree cone for spawning
        // at the edges, so asteroids don't run parallel to the sides they spawn at
        dir /= 4.0f;
        switch (spawnSide) {
            case 0:
                spawnX = -radius;
                dir -= 0.0f;
                break;
            case 1:
                spawnY = -radius;
                dir -= PI/2.0f;
                break;
            case 2:
                spawnX = SCREEN_WIDTH+radius;
                dir += PI;
                break;
            case 3:
                spawnY = SCREEN_HEIGHT+radius;
                dir += PI/2.0f;
                break;
        }
    }
    Asteroid newAsteroid(spawnX, spawnY, spawnSize, speed*cos(dir), speed*sin(dir), radius, ASTEROID_COLOR);
    asteroidList.push_back(newAsteroid);
    return;
}

void Game::createBullet (Bullet *newBullet) {
    bulletList.push_back(*newBullet);
    return;
}

bool Game::asteroidHitsPlayer(Asteroid *asteroid) {
    double maxDist = (asteroid->getRadius()+player.getRadius()/3)*
                     (asteroid->getRadius()+player.getRadius()/3);
    return  (asteroid->getXPos()-player.getXPos())*(asteroid->getXPos()-player.getXPos()) +
            (asteroid->getYPos()-player.getYPos())*(asteroid->getYPos()-player.getYPos()) < maxDist;
}

void Game::checkCollision (void) {
    int totalAsteroids = asteroidList.size();
    int totalProjectiles = bulletList.size();
    
    for(int i = 0; i < totalAsteroids; i++) {
        for(int j = 0; j < totalProjectiles; j++) {
            if(totalAsteroids == 0) {
                break;
            }
            if(projectileHits(&asteroidList[i], &bulletList[j])) {
                std::vector<Asteroid>::iterator itA = asteroidList.begin() + i;
                splitAsteroid(itA);
                
                std::vector<Bullet>::iterator itB = bulletList.begin() + j;
                destroyBullet(itB);
                
                totalProjectiles--;
                totalAsteroids--;
            }
        }
    }
    if(!gameOver && !(invincibleTime > EPSILON)) {
        for(int i = 0; i < totalAsteroids; i++) {
            if(asteroidHitsPlayer(&asteroidList[i])) {
                gameOver = true;
                player.selfDestruct();
                for(int i = 0; i < 100; i++) {
                    double dir = static_cast<double>(i)*2.0f*PI/100.0f;
                    Bullet newBullet = Bullet(player.getXPos(),
                                              player.getYPos(),
                                              PROJECTILE_RADIUS,
                                              PROJECTILE_SPEED*cos(dir),
                                              PROJECTILE_SPEED*sin(dir),
                                              PROJECTILE_COLOR);
                    createBullet(&newBullet);
                }
            }
        }
    }
    return;
}

bool Game::projectileHits (Asteroid *asteroid, Bullet *bullet) {

    double maxDist = (asteroid->getRadius()+bullet->getRadius()/3)*
                     (asteroid->getRadius()+bullet->getRadius()/3);
    return (asteroid->getXPos()-bullet->getXPos())*(asteroid->getXPos()-bullet->getXPos()) +
                 (asteroid->getYPos()-bullet->getYPos())*(asteroid->getYPos()-bullet->getYPos()) <
                  maxDist;
}


void Game::splitAsteroid(std::vector<Asteroid>::iterator toSplit) {
    int newSize = toSplit->getSize()-1;
    int newXPos = toSplit->getXPos();
    int newYPos = toSplit->getYPos();
    destroyAsteroid(toSplit);
    
    if(newSize != 0) {
        createAsteroid(newSize, newXPos, newYPos);
        createAsteroid(newSize, newXPos, newYPos);
    }
    return;
}

void Game::destroyAsteroid (std::vector<Asteroid>::iterator it) {
    createExplosion(PARTICLES_PER_EXPLOSION[it->getSize()], it->getXPos(), it->getYPos(), it->getSize());
    asteroidList.erase(it);
}

void Game::destroyBullet (std::vector<Bullet>::iterator it) {
    bulletList.erase(it);
}

void Game::destroyParticle (std::vector<Particle>::iterator it) {
    particleList.erase(it);
}

void Game::fire (double mouseX, double mouseY, double timeStep) {
    if((weaponCoolDownTime < EPSILON && !gameOver) ||
       (rapidFireTime > EPSILON && weaponCoolDownTime/3.0f < EPSILON)) {
        double dir = atan2(mouseY-player.getYPos(),mouseX-player.getXPos());
        for(int i = 0; i < player.getWeapon()->getNumBullets(); i++) {
            Bullet newBullet = player.getWeapon()->getBullet(i, player.getXPos(), player.getYPos(), dir);
            createBullet(&newBullet);
        }
        weaponCoolDownTime = player.getWeapon()->getFireRate();
    }
    return;
}

void Game::createExplosion (int particles, double x, double y, int size) {
    for(int i = 0; i < particles; i++) {
        if(particleList.size() > MAX_PARTICLES) {
            break;
        }
        double angle = getRandomDir();
        double sx = cos(angle)*getExplosionParticleSpeed(size);
        double sy = sin(angle)*getExplosionParticleSpeed(size);
        Particle newParticle(x,
                             y,
                             EXPLOSION_PARTICLE_RADIUS,
                             sx,
                             sy,
                             EXPLOSION_PARTICLE_COLOR,
                             getExplosionParticleLifeSpan(size)-(rand()%10)*0.01f);
        particleList.push_back(newParticle);
    };
}

void Game::activatePowerUp (powerUpType power) {
    switch (power) {
        case EXPLOSION:
            for(int i = 0; i < 100; i++) {
                double dir = static_cast<double>(i)*2.0f*PI/100.0f;
                double delta = 0.9f + 0.1f*((i%5)/4.0f);
                Bullet newBullet = Bullet(player.getXPos(),
                                          player.getYPos(),
                                          PROJECTILE_RADIUS,
                                          (delta*PROJECTILE_SPEED)*cos(dir),
                                          (delta*PROJECTILE_SPEED)*sin(dir),
                                          PROJECTILE_COLOR);
                createBullet(&newBullet);
            }
            for(int i = 0; i < 100; i++) {
                double dir = static_cast<double>(100-i)*2.0f*PI/100.0f;
                double delta = 0.9f + 0.1f*((i%5)/4.0f);
                Bullet newBullet = Bullet(player.getXPos(),
                                          player.getYPos(),
                                          PROJECTILE_RADIUS,
                                          (delta*PROJECTILE_SPEED)*cos(dir),
                                          (delta*PROJECTILE_SPEED)*sin(dir),
                                          PROJECTILE_COLOR);
                createBullet(&newBullet);
            }
            break;
        case RAPID_FIRE:
            rapidFireTime = 7.0f;
            break;
        case SLOW_TIME:
            slowDownTime = 5.0f;
            break;
        case INVINCIBLE:
            invincibleTime = 5.0f;
            break;
    }
}


void Game::reset (void) {
    gameOver = false;
    roundNum = 0;
    weaponCoolDownTime = 0.0f;
    asteroidList.clear();
    bulletList.clear();
    player = Player(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, PLAYER_RADIUS, 0, 0, PLAYER_COLOR);
    return;
}













