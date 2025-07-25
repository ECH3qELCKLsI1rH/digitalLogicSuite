#include <SFML/Graphics.hpp>

int main(int argc, char **argv)
{
    unsigned int width = 640;
    unsigned int height = 360;
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode({width, height}), "Test");
    window->setFramerateLimit(60);

    sf::CircleShape circle(90.0f);

    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition({width / 2.0f, height / 2.0f});
    circle.setFillColor(sf::Color::Green);
    circle.setOutlineThickness(3.0f);
    circle.setOutlineColor(sf::Color::Red);

    while (window->isOpen())
    {
        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window->close();
            }
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window->close();
                }
            }
        }
        window->clear(sf::Color::White);

        window->draw(circle);

        window->display();
    }
    delete window;
    return 0;
}