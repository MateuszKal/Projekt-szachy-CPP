#include "Button.h"

Button::Button(sf::RectangleShape rect_, sf::Text text_)// by text
{
	rect = rect_;
	text = text_;
	state = "off";

	rect.setPosition(text.getPosition());
	//text.setCharacterSize(rect_.getPosition().x-2);
	std::string a = text.getString();

	std::cout << a <<'\n';
	//rect->setSize(sf::Vector2f(text.getLocalBounds().width + 10, text.getCharacterSize() + 10));
	rect.setSize(sf::Vector2f(100, 100));
	rect.move(sf::Vector2f(0, 0));
}

Button::Button(const std::string& textStr, float x, float y) 
{
        // Załaduj czcionkę
        if (!font.loadFromFile("font/arial.ttf")) {
            // Obsługa błędu, jeśli czcionka się nie załaduje
            //std::cerr << "Nie udało się załadować czcionki!" << std::endl;
			std::cout<<"arial błąd\n";
			return;
        }

        // Inicjalizuj prostokąt
        rect.setSize(sf::Vector2f(200.f, 50.f));  // Szerokość 200px, wysokość 50px
        rect.setFillColor(sf::Color::Blue);  // Kolor przycisku
        rect.setPosition(x, y);  // Pozycja przycisku w oknie

        // Ustawienia tekstu
        text.setFont(font);
        text.setString(textStr);  // Ustaw tekst
        text.setCharacterSize(24);  // Rozmiar tekstu
        text.setFillColor(sf::Color::White);  // Kolor tekstu
        text.setPosition(
            x + (rect.getSize().x - text.getLocalBounds().width) / 2,  // Wyrównanie tekstu w poziomie
            y + (rect.getSize().y - text.getLocalBounds().height) / 2  // Wyrównanie tekstu w pionie
		);
}
    


Button::Button() {
        rect.setSize(sf::Vector2f(200.f, 50.f));  // Domyślny rozmiar przycisku
        rect.setFillColor(sf::Color::Blue);        // Kolor tła przycisku
        rect.setPosition(100.f, 100.f);            // Pozycja przycisku (możesz zmienić)

                              // Ustawienie czcionki
        text.setString("Kliknij mnie");            // Domyślny tekst
        text.setCharacterSize(24);                // Rozmiar tekstu
        text.setFillColor(sf::Color::White);      // Kolor tekstu
        text.setPosition(120.f, 115.f); 
    }

void Button::gets()
{
	std::cout<<"Button\n";
	std::cout << rect.getPosition().x << '\n';
	std::cout << rect.getPosition().y << '\n';
	std::cout << rect.getScale().x << '\n';
	std::cout << rect.getScale().y << '\n';
	std::cout << rect.getLocalBounds().height << '\n';
	std::cout << rect.getLocalBounds().width << '\n';
	std::cout << rect.getLocalBounds().top << '\n';
	std::cout << rect.getLocalBounds().left << '\n';
}

void Button::chState(sf::RenderWindow& window)
{
	//std::cout<<"f un "<<sf::Mouse::getPosition(window).x <<" "<<sf::Mouse::getPosition(window).y<<'\n';
	//std::cout<<rect.getPosition().x<<" "<<rect.getPosition().y<<" rect ex\n";
	if ((sf::Mouse::getPosition(window).x >= rect.getPosition().x) &&
		(sf::Mouse::getPosition(window).x <= rect.getPosition().x + rect.getLocalBounds().width) &&
		(sf::Mouse::getPosition(window).y >= rect.getPosition().y) &&
		(sf::Mouse::getPosition(window).y <= rect.getPosition().y + rect.getLocalBounds().height))
	{
		//std::cout<<"exit\n";
		state = "hover";
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			state = "pressed";
		}

	}
	else state = "off";
}

std::string Button::getstate()
{
	return state;
}

sf::RectangleShape* Button::getRect()
{
	return &rect;
}

void Button::display(sf::RenderWindow& window)
{
	//std::cout << text.getLocalBounds().width;
	//std::cout<<"a\n";
	window.draw(rect);
	//std::cout<<"b\n";
	try{
	window.draw(text);
	}
	catch (...) {std::cout<<"NIEZNANY\n";}
	//std::cout<<"c\n";
}

void Button::set_color(sf::Color c)
{
	rect.setFillColor(c);
}