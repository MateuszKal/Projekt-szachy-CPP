#include <iostream>
#include "Board_screen.h"
#include "Menu_screen.h"

//
//int main()
//{
//
//	//Board w klasie "okno gry" w oknie potencjalnie bedzie tablica dostepnych, wybrana aktualnie biuerka(x, y)
//	//std::cout << "abca";
//	return 0;
//}

void basic_events(sf::Event& e, sf::RenderWindow& w)
{
    //std::cout << "ahoj1";
    if (e.type == sf::Event::Closed)
    {
        //std::cout << "ahoj";
        w.close();
    }
}

std::string window_state;
static sf::Font font;
int main()
{
    Board aaa;
    sf::Text t;
    sf::Texture a;
    sf::Font b;
    sf::RenderWindow window(sf::VideoMode(1100, 900), "Project Chess", sf::Style::Close);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    sf::Font font;


    // Load it from a file
    if (!font.loadFromFile("font/arial.ttf"))
    {
        std::cout << "blad czcionka\n";
    }
    sf::Text np;
    np.setString("aasda");
    np.setFont(font); // font is a sf::Font
    np.setCharacterSize(15);
    np.setFillColor(sf::Color::White);
    np.setStyle(sf::Text::Bold);
    np.setPosition(50 + (100 ), 50 + (100));


    Menu_screen men;

    //Board_screen bos(window);
    while (window.isOpen())
    {
        Board_screen bos(window);

        
        men.play(window, basic_events);
        if (Menu_screen::wyb==1)
        {
            char s[2]={'P','P'};
            bos.play(window, basic_events,s);
        }
        else if (Menu_screen::wyb==2)
        {   
            char s[2]={'P','C'};
            bos.play(window, basic_events,s);
        }
        /*sf::Event event;
        window.pollEvent(event);
        while (window.pollEvent(event))
        {
            basic_events(event, window);
        }*/


        


        Menu_screen::wyb =0;
       /* window.clear();
        window.draw(np);
        window.display();*/
    }

    return 0;
}