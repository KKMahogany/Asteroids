
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "game.h"

#include <GLUT/GLUT.h>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

int main(int argc, char const *argv[]) {
    srand(time(0));

    
    
    sf::Clock globalClock;
    Game *game = new Game;
    
    game->setPlayerWeapon(Weapon());
    
    
    // Start the game loop
    
    sf::Keyboard keyboard;
    sf::Mouse mouse;
    
    
    while (game->getWindow()->isOpen()) {
        if(game->isGameOver() && keyboard.isKeyPressed(sf::Keyboard::R)) {
            game->reset();
        }
        sf::Time curTime = globalClock.restart();
        
        game->update(curTime.asSeconds());

        double accelX = 0.0f;
        double accelY = 0.0f;
        
        if(keyboard.isKeyPressed(sf::Keyboard::S)) {
            accelY += PLAYER_ACCELERATION;
        }
        if(keyboard.isKeyPressed(sf::Keyboard::W)) {
            accelY -= PLAYER_ACCELERATION;
        }
        
        if(keyboard.isKeyPressed(sf::Keyboard::D)) {
            accelX += PLAYER_ACCELERATION;
        }
        if(keyboard.isKeyPressed(sf::Keyboard::A)) {
            accelX -= PLAYER_ACCELERATION;
        }
        // TODO: Move weapon switching into a Game function
        if(keyboard.isKeyPressed(sf::Keyboard::Num1)) {
            game->setPlayerWeapon(getWeapon(CHAIN_GUN));
        }
        if(keyboard.isKeyPressed(sf::Keyboard::Num2)) {
            game->setPlayerWeapon(getWeapon(SPREAD_SHOT));
        }
        if(keyboard.isKeyPressed(sf::Keyboard::Num3)) {
            game->setPlayerWeapon(getWeapon(SPLINTER_GUN));
        }
        if(keyboard.isKeyPressed(sf::Keyboard::Num4)) {
            game->setPlayerWeapon(getWeapon(MINE_LAYER));
        }
        if(keyboard.isKeyPressed(sf::Keyboard::Num5)) {
            game->setPlayerWeapon(getWeapon(CANNON));
        }
        if(keyboard.isKeyPressed(sf::Keyboard::Num6)) {
            game->activatePowerUp(SLOW_TIME);
        }
        game->acceleratePlayer(accelX, accelY, curTime.asSeconds());
        
        game->checkCollision();

        if(keyboard.isKeyPressed(sf::Keyboard::Space)) {
            game->fire(mouse.getPosition(*game->getWindow()).x,
                       mouse.getPosition(*game->getWindow()).y, curTime.asSeconds());
        }
        
        sf::Event event;
        while (game->getWindow()->pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                game->getWindow()->close();
            }

            // Escape pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                game->getWindow()->close();
            }
        }

        // Output to screen
        game->getWindow()->clear();
        game->drawScene();
        game->getWindow()->display();
        
    }
    
    return EXIT_SUCCESS;
}
