
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "asteroid.hpp"
#include "functions.hpp"
#include "laser.hpp"
#include "position.hpp"
#include "ship.hpp"

using namespace std;

const double WIN_WIDTH = 1400;
const double WIN_HEIGHT = 1400;

int main() {

/// Creating game window and setting framerate limit

    sf::ContextSettings settings; /// antialiasing to smooth shapes
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "ASTEROIDS!", sf::Style::Default, settings);

    window.setFramerateLimit(60);

/// Loading background texture

    sf::Texture stars;

    if (!stars.loadFromFile("../graphics/stars.png")) {
        cout << "Error loading background." << endl;
        return 0;
    }

    sf::Sprite background(stars);

/// Creating player ship and the vectors of Asteroids and Bullets

    Ship ship = Ship();

/// Beginning main game loop and showing Start Menu

    sf::Event event;

    while (window.waitEvent(event)) {

        displayStartScreen(window);

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
            break;
        }
    }

    while (window.isOpen()) {
        window.clear();
        window.draw(background);

        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

/// User input (keypress events)

        /// Rotate counterclockwise with left arrow key

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            ship.RotateIncrement(-5);
        }

        /// Increase thrust with up arrow key

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            ship.changeSpeed(2);
        } else {
            ship.changeSpeed(-1);
        }

        /// Rotate clockwise with right arrow key

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            ship.RotateIncrement(5);
        }
        ship.UpdatePosition();
        ship.draw(window);

        /// Fire bullets with space key and push them back into vector

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            // fire
        }

// If ship hits asteroid, display game over screen
        
        bool collision = false;
        if (collision) {

            displayGameOverScreen(window);

            while (window.waitEvent(event)) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
                    break;
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
                    window.close();
                }
            }
        }

/// Updating positions and redrawing asteroids

        window.display();
    }
    return 0;
}
