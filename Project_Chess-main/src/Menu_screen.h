#ifndef menu_h
#define menu_h

#include <iostream>
#include "Button.h"

class Menu_screen
{
    typedef void(*Actions)(sf::Event& e, sf::RenderWindow& w);
    Button* p1;
    Button* p2;
    

public:
    static int wyb;
    Menu_screen();

    void play(sf::RenderWindow& w, Actions basic_events);
};

#endif