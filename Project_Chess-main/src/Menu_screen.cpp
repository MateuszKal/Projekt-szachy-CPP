#include "Menu_screen.h"
    int Menu_screen::wyb;
    Menu_screen::Menu_screen()
    {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(100, 100));  // Kwadrat o boku 100
        rect.setFillColor(sf::Color::Blue);
        rect.setPosition(350, 250);            // Ustawienie na środku okna

        // Tworzenie tekstu
        
        
        p1 = new Button("2 players",100,100);
        p2 = new Button("vs comp",100,200);

        // Tworzenie obiektu Button
        //p1 = new Button(rect, text);
    }

    void Menu_screen::play(sf::RenderWindow& w, Actions basic_events)
    {
        int flag = 0;
            sf::Cursor cursor;
            cursor.loadFromSystem(sf::Cursor::Hand);

            while (wyb == 0)
            {
                w.setMouseCursor(cursor);

                sf::Event event;
                // window.pollEvent(event);

                while (w.pollEvent(event))
                {
                    //akt bier


                //std::cout << "EVENT borad cren\n";
                    basic_events(event, w);

                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        std::cout << "pressed444\n";
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            p1->chState(w);
                            p2->chState(w);

                            if (p1->getstate()=="pressed")
                            {
                                std::cout<<"buttonp1\n";
                                Menu_screen::wyb = 1;
                                break;
                            }
                            else if (p2->getstate()=="pressed")
                            {
                                std::cout<<"buttonp1\n";
                                Menu_screen::wyb = 2;
                                break;
                            }
                        }
                    }
                }

                w.clear();
                
                p1->display(w);
                p2->display(w);

                w.display();
            }
    }

