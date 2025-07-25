// #include <SFML/Graphics.hpp>
#include <iostream>

#include "src/truthTable_with_expression_simplifier.h"

int main(int argc, char **argv) {
    TruthTableGenerator ttg;
    ttg.readExpression();
    ttg.generateTruthTable();
    std::cout << "\nSimplified: " << ttg.simplifyExpression() << std::endl;
    // unsigned int width = 640;
    // unsigned int height = 360;
    // sf::RenderWindow window(sf::VideoMode({width, height}), "Test");
    // window.setFramerateLimit(60);

    // sf::CircleShape circle(90.0f);

    // circle.setOrigin(circle.getGeometricCenter());
    // circle.setPosition({width / 2.0f, height / 2.0f});
    // circle.setFillColor(sf::Color::Magenta);
    // circle.setOutlineThickness(3.0f);
    // circle.setOutlineColor(sf::Color::Red);

    // while (window.isOpen()) {
    //     while (const std::optional event = window.pollEvent()) {
    //         if (event->is<sf::Event::Closed>()) {
    //             window.close();
    //         } else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
    //             if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
    //                 window.close();
    //             }
    //         }
    //     }
    //     window.clear(sf::Color::White);

    //     window.draw(circle);

    //     window.display();
    // }
    // return 0;
}