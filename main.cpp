#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

enum State
    {
        Playing,
        Paused,
        Finished
    };

void generateArray(std::vector<int> &hodnoty)
{
    int count = hodnoty.size();
    std::random_device random;
    std::mt19937 gen(random());
    std::uniform_int_distribution<int> distInt(1, count);

    for (int i = 0; i < count; i++)
    {
        int value = distInt(gen);
        hodnoty[i] = value;
    }
}
void bubbleStep(std::vector<int>& hodnoty, int& i, int& j, int amount, bool& sorted, State& state) {

    if (hodnoty[j] > hodnoty[j+1])
    {
        std::swap(hodnoty[j], hodnoty[j+1]);
    }
    j++;

    if (j >= amount -1 -i)
    {
        j = 0;
        i++;
    }
    
    if (i >= amount -1)
    {
        sorted = true;
        state = State::Finished;
    }
    
}
void resetSorting (int& i, int& j, std::vector<int>& hodnoty, bool& sorted, State& state, std::chrono::time_point<std::chrono::high_resolution_clock>& startTime, int amount) {
    i = 0;
    j = 0;
    sorted = false;
    state = State::Paused;
    startTime = std::chrono::high_resolution_clock::now();
    hodnoty.clear();
    hodnoty.resize(amount);
    generateArray(hodnoty);
}

int main()
{
    int windowHeight = 600;
    int windowWidth = 1000;
    bool sorted = false;
    int i = 0;
    int j = 0;
    sf::RectangleShape rec;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sorting");
    int amount;
    std::cout << "Enter amount of rectangle: ";
    std::cin >> amount;
    std::vector<int> hodnoty;
    int maxValue = amount;
    auto startTime = std::chrono::high_resolution_clock::now();
    hodnoty.resize(amount);
    generateArray(hodnoty);

    float widthColumn = static_cast<float>(windowWidth) / amount;
    float scale = static_cast<float>(windowHeight) / amount;
    State state = State::Paused;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    if (state == State::Paused)
                        state = State::Playing;
                    else
                        state = State::Paused;
                }

                if (event.key.code == sf::Keyboard::R)
                {
                    resetSorting(i, j, hodnoty, sorted, state, startTime, amount);
                }
                
            }
        }
        window.clear(sf::Color::Black);

        if (state == State::Playing)
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
            bubbleStep(hodnoty, i, j, amount, sorted, state);
            
            std::cout << elapsed.count() << "ms    \r";

        }
        else if (state == State::Paused)
        {
        }

        for (int index = 0; index < amount; index++)
        {
            float heightColumn = hodnoty[index] * scale;
            float x = widthColumn * index;
            float y = windowHeight - heightColumn;

            rec.setSize(sf::Vector2f(widthColumn, heightColumn));
            rec.setPosition(sf::Vector2f(x, y));

            if (sorted)
            {
                rec.setFillColor(sf::Color(0, 220, 120));
            }
            else if (state == State::Playing && index == j)
            {
                rec.setFillColor(sf::Color::White);
            }
            else if (index >= amount - i - 1)
            {
                rec.setFillColor(sf::Color(0, 230, 180));
            }
            else
            {
                rec.setFillColor(sf::Color(0, 145, 255));
            }

            window.draw(rec);
        }

        window.display();
    }
}