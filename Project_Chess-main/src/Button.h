#ifndef button_h
#define button_h

#include <SFML/Graphics.hpp>
#include <iostream>


class Button
{
	public :sf::RectangleShape rect;
	public :sf::Text text;
	public :std::string state;
	public :sf::Font font;

public:
	Button(sf::RectangleShape rect_, sf::Text text_);
	Button(const std::string& textStr, float x, float y);
	Button();
	void gets();

	sf::RectangleShape* getRect();

	void chState(sf::RenderWindow& window);

	std::string getstate();

	void display(sf::RenderWindow& window);

	void set_color(sf::Color c);
};

#endif