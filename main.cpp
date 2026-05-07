#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>

void generateArray(std::vector<int> &array)
{
}

int main()
{
    int windowHeight = 600;
    int windowWidth = 1000;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sorting");
    std::vector<int> hodnoty;
    hodnoty.reserve(100);

    std::random_device random;
    std::mt19937 gen(random());
    std::uniform_int_distribution<int> distInt(1, 100);

    for (int i = 0; i < 100; i++)
    {
        int value = distInt(gen);
        hodnoty.push_back(value);
        std::cout << value << std::endl;
    }
    int widthColumn = windowWidth / 100;
    int scale = windowHeight / 100;
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        for (int i = 0; i < hodnoty.size(); i++)
        {
            int heightColumn = hodnoty[i] * scale;
            int x = widthColumn * i;
            int y = windowHeight - heightColumn;
            
            sf::RectangleShape rec;
            rec.setSize(sf::Vector2f(widthColumn, heightColumn));
            rec.setPosition(sf::Vector2f(x, y));
            rec.setFillColor(sf::Color::Blue);
            window.draw(rec);
        }
        window.display();
    }
}