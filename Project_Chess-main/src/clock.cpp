#include "clock.h"

    Clock_c::Clock_c(float timeLimit) 
        : whiteTime(timeLimit), blackTime(timeLimit), 
          currentPlayer(Player::White), clockRunning(false) {
        font.loadFromFile("font/arial.ttf");  // Załaduj czcionkę
        timeText.setFont(font);
        timeText.setCharacterSize(30);
        timeText.setFillColor(sf::Color::White);
    }

    void Clock_c::start() {
        clockRunning = true;
        clock.restart();
    }

    void Clock_c::stop() {
        clockRunning = false;
    }

    void Clock_c::switchPlayer() {
        if (currentPlayer == Player::White) {
            currentPlayer = Player::Black;
            whiteTime -= clock.getElapsedTime().asSeconds();
            clock.restart();
        } else {
            currentPlayer = Player::White;
            blackTime -= clock.getElapsedTime().asSeconds();
            clock.restart();
        }
    }

    void Clock_c::update() {
        if (clockRunning) {
            float elapsed = clock.getElapsedTime().asSeconds();
            if (currentPlayer == Player::White) {
                whiteTime -= elapsed;
            } else {
                blackTime -= elapsed;
            }
            clock.restart();
        }
    }

    void Clock_c::draw(sf::RenderWindow& window) {
        std::ostringstream timeStream;
        timeStream.precision(2);
        timeStream << std::fixed;

        if (currentPlayer == Player::White) {
            timeStream << "White: " << whiteTime;
        } else {
            timeStream << "Black: " << blackTime;
        }

        timeText.setString(timeStream.str());
        timeText.setPosition(sf::Vector2f(200.f, 10.f));
        window.draw(timeText);
    }

    bool Clock_c::isRunning() const {
        return clockRunning;
    }
