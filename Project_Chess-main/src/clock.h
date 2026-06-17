#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>

class Clock_c {
public:
    Clock_c(float timeLimit);

    void start();

    void stop();

    void switchPlayer();

    void update();

    void draw(sf::RenderWindow& window);

    bool isRunning() const;
private:
    enum class Player { White, Black };
    
    sf::Clock clock;
    sf::Font font;
    sf::Text timeText;
    float whiteTime;
    float blackTime;
    Player currentPlayer;
    bool clockRunning;
};