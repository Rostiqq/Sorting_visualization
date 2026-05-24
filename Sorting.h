#pragma once
#include <vector>
#include <chrono>
#include <SFML/Graphics.hpp>

enum class Algorithm
{
    Bubble,
    Selection
};

enum class State
{
    Paused,
    Playing,
    Finished
};

class Sorting
{
private:
    sf::RectangleShape rec;

    std::vector<int> hodnoty;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    double elapsedTime = 0.0;
    int windowHeight = 600;
    int windowWidth = 800;
    float widthColumn;
    float scale;
    int amount;

    bool timerStarted = false;
    int i;
    int j;
    int minIndex;

    State state;
    Algorithm algorithm;

public:
    Sorting(int amount,int width = 800, int height = 600);

    void generateArray();
    void reset();
    void setupBar(int index);
    void applyBubbleColor(int index);
    void applySelectionColor(int index);
    
    void bubbleStep();
    void selectionStep();

    void render(sf::RenderWindow &window);
    void renderBubble(sf::RenderWindow &window);
    void renderSelection(sf::RenderWindow &window);

    void handleInput(sf::Event &event);

    void update();
};