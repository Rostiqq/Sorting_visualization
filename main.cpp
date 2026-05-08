#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>

int main()
{
    int windowHeight = 600;
    int windowWidth = 1000;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sorting");
    int amount;
    std::cout<<"Enter amount of rectangle: ";
    std::cin>>amount;
    std::vector<int> hodnoty;
    int maxValue = amount;
    std::random_device random;
    std::mt19937 gen(random());
    std::uniform_int_distribution<int> distInt(1, amount);

    for (int i = 0; i < amount; i++)
    {
        int value = distInt(gen);
        hodnoty.push_back(value);
        std::cout << value << std::endl;
    }
    float widthColumn = static_cast<float>(windowWidth) / amount;
    float scale = static_cast<float>(windowHeight)/ amount;
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        for (int i = 0; i < amount; i++)
        {
            float heightColumn = hodnoty[i] * scale;
            float x = widthColumn * i;
            float y = windowHeight - heightColumn;
            
            sf::RectangleShape rec;
            rec.setSize(sf::Vector2f(widthColumn, heightColumn));
            rec.setPosition(sf::Vector2f(x, y));
            rec.setFillColor(sf::Color::Blue);
            window.draw(rec);
        }
        window.display();
    }
}