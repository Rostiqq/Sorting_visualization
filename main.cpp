#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "TEST");

    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        std::cout << "Start\n";

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(shape);   
        window.display();
    }
}