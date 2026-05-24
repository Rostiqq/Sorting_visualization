
#include <vector>
#include <chrono>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Sorting.h"

Sorting::Sorting(int amount, int width, int height)
{
    this->amount = amount;
    this->windowWidth = width;
    this->windowHeight = height;

    algorithm = Algorithm::Bubble;
    state = State::Paused;

    reset();
}

void Sorting::generateArray()
{
    std::random_device random;
    std::mt19937 gen(random());
    std::uniform_int_distribution<int> distInt(1, amount);

    for (int i = 0; i < amount; i++)
    {
        int value = distInt(gen);
        hodnoty[i] = value;
    }
}

void Sorting::bubbleStep()
{
    if (j + 1 < amount && hodnoty[j] > hodnoty[j + 1])
    {
        std::swap(hodnoty[j], hodnoty[j + 1]);
    }
    j++;

    if (j >= amount - 1 - i)
    {
        j = 0;
        i++;
    }

    if (i >= amount - 1)
    {
        state = State::Finished;

        auto endTime = std::chrono::high_resolution_clock::now();
        elapsedTime = std::chrono::duration<double>(endTime - startTime).count();

        std::cout << "Bubble Sort - time: " << elapsedTime << " s" << std::endl;
        return;
    }
}

void Sorting::selectionStep()
{
    if (hodnoty[j] < hodnoty[minIndex])
    {
        minIndex = j;
    }

    j++;

    if (j >= amount)
    {
        std::swap(hodnoty[i], hodnoty[minIndex]);

        i++;

        if (i >= amount - 1)
        {
            state = State::Finished;
            auto endTime = std::chrono::high_resolution_clock::now();
            elapsedTime = std::chrono::duration<double>(endTime - startTime).count();

            std::cout << "Selection Sort - time: " << elapsedTime << " s" << std::endl;
            return;
        }

        minIndex = i;
        j = i + 1;
    }
}

void Sorting::reset()
{

    widthColumn = static_cast<float>(windowWidth) / amount;
    scale = static_cast<float>(windowHeight) / amount;
    i = 0;
    j = 0;
    minIndex = 0;

    state = State::Paused;
    startTime = std::chrono::high_resolution_clock::now();
    hodnoty.clear();
    hodnoty.resize(amount);
    generateArray();
}

void Sorting::setupBar(int index)
{
    float heightColumn = static_cast<float>(hodnoty[index]) * scale;

    float x = widthColumn * index;
    float y = windowHeight - heightColumn;

    rec.setSize(sf::Vector2f(widthColumn, heightColumn));
    rec.setPosition(sf::Vector2f(x, y));
}

void Sorting::applyBubbleColor(int index)
{
    if (state == State::Finished)
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
}

void Sorting::render(sf::RenderWindow &window)
{

    switch (algorithm)
    {
    case Algorithm::Bubble:
        renderBubble(window);
        break;

    case Algorithm::Selection:
        renderSelection(window);
        break;
    }
}

void Sorting::renderBubble(sf::RenderWindow &window)
{
    for (int index = 0; index < amount; index++)
    {
        setupBar(index);
        applyBubbleColor(index);
        window.draw(rec);
    }
}

void Sorting::applySelectionColor(int index)
{
    if (state == State::Finished)
    {
        rec.setFillColor(sf::Color(0, 220, 120));
    }
    else if (state == State::Playing && index == j)
    {
        rec.setFillColor(sf::Color::White);
    }
    else if (index < i)
    {
        rec.setFillColor(sf::Color(0, 230, 180));
    }
    else
    {
        rec.setFillColor(sf::Color(0, 145, 255));
    }
}

void Sorting::renderSelection(sf::RenderWindow &window)
{
    for (int index = 0; index < amount; index++)
    {
        setupBar(index);
        applySelectionColor(index);
        window.draw(rec);
    }
}

void Sorting::handleInput(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Space)
        {
            if (state == State::Paused)
            {
                state = State::Playing;
                if (!timerStarted)
                {
                    startTime = std::chrono::high_resolution_clock::now();
                    timerStarted = true;
                }
            }
            else
            {
                state = State::Paused;
            }
        }

        if (event.key.code == sf::Keyboard::R)
        {
            reset();
            timerStarted = false;
        }

        if (event.key.code == sf::Keyboard::Num1)
        {
            algorithm = Algorithm::Bubble;
            reset();
            timerStarted = false;
        }

        if (event.key.code == sf::Keyboard::Num2)
        {
            algorithm = Algorithm::Selection;
            reset();
            timerStarted = false;
        }
    }
}

void Sorting::update()
{
    if (state != State::Playing)
        return;

    switch (algorithm)
    {
    case Algorithm::Bubble:
        bubbleStep();
        break;

    case Algorithm::Selection:
        selectionStep();
        break;
    }
}