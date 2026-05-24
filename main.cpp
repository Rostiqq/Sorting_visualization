#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sorting.h"

const unsigned int windowWidth = 800;
const unsigned int windowHeight = 600;

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(windowWidth, windowHeight),
        "Sorting");

    int amount;

    std::cout << "Enter amount of rectangles: ";
    std::cin >> amount;

    Sorting sort(amount,windowWidth,windowHeight);

    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            sort.handleInput(event);
        }

        sort.update();

        window.clear();

        sort.render(window);

        window.display();
    }
}