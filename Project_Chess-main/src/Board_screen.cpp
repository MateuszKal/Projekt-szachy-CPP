#include "Board_screen.h"

sf::Texture* Board_screen::get_piece_txt(Piece* p)
{
    if (p->get_side() == 0)
    {
        switch (p->get_type())
        {
        case 'p':
            return &p0_t;
            break;
        case 'N':
            return &n0_t;
            break;
        case 'B':
            return &b0_t;
            break;
        case 'R':
            return &r0_t;
            break;
        case 'Q':
            return &q0_t;
            break;
        case 'K':
            return &k0_t;
            break;
        }
    }
    else
    {
        if (p->get_side() == 1)
        {
            switch (p->get_type())
            {
            case 'p':
                return &p1_t;
                break;
            case 'N':
                return &n1_t;
                break;
            case 'B':
                return &b1_t;
                break;
            case 'R':
                return &r1_t;
                break;
            case 'Q':
                return &q1_t;
                break;
            case 'K':
                return &k1_t;
                break;
            }
        }
    }
return nullptr;
}

Board_screen::Board_screen(sf::RenderWindow& w): mat_o(Button("Mat",0,0)),
clockk(Clock_c(300.0f))
{
    //std::vector < sf::RectangleShape > kaf;
    side[1] = 'P'; // bialy
    side[0] = 'C'; // czarny

    mat_o.set_color(sf::Color::Red);

    sf::RectangleShape kaf[8][8];
    //std::cout << "abc";
    sf::Color col;
    col = sf::Color::Blue;

    for (int i = 0; i < 8; i++)
    {
        for (int x = 0; x < 8; x++)
        {
            sf::RectangleShape a;
         
            a.setFillColor(col);
            
            a.setOutlineThickness(0);
            kaf[x][i]=a;
            if (col == sf::Color::White) col = sf::Color::Blue;
            else col = sf::Color::White;
        }
        if (col == sf::Color::White) col = sf::Color::Blue;
        else col = sf::Color::White;
    }
    /*white_field.setFillColor(sf::Color::Wh   ite);
    white_field.setOutlineThickness(0); */

   /* black_field.setFillColor(sf::Color::Green);
    black_field.setOutlineThickness(0);*/

    sf::Text np[8][8];
    sf::Font* font = new sf::Font;

    if (!movie_tex.loadFromFile("img/image.png", sf::IntRect(0, 0, 100, 100)))
    {
        std::cout << "reeeerrr";
        // error...
    }

    if (!pressed_tex.loadFromFile("img/selected1.png", sf::IntRect(0, 0, 100, 100)))
    {
        std::cout << "reeeerrr";
        // error...
    }

    //load pieces tex
    p0_t.loadFromFile("img/p0.png", sf::IntRect(0, 0, 100, 100));
    p1_t.loadFromFile("img/p1.png", sf::IntRect(0, 0, 100, 100));
    n0_t.loadFromFile("img/N0.png", sf::IntRect(0, 0, 100, 100));
    n1_t.loadFromFile("img/N1.png", sf::IntRect(0, 0, 100, 100));
    b0_t.loadFromFile("img/B0.png", sf::IntRect(0, 0, 100, 100));
    b1_t.loadFromFile("img/B1.png", sf::IntRect(0, 0, 100, 100));
    r0_t.loadFromFile("img/R0.png", sf::IntRect(0, 0, 100, 100));
    r1_t.loadFromFile("img/R1.png", sf::IntRect(0, 0, 100, 100));
    q0_t.loadFromFile("img/Q0.png", sf::IntRect(0, 0, 100, 100));
    q1_t.loadFromFile("img/Q1.png", sf::IntRect(0, 0, 100, 100));
    k0_t.loadFromFile("img/K0.png", sf::IntRect(0, 0, 100, 100));
    k1_t.loadFromFile("img/K1.png", sf::IntRect(0, 0, 100, 100));


    // Load it from a file
    if (!font->loadFromFile("font/arial.ttf"))
    {
        std::cout << "czcionka blad\n";
    }


    field = new Button * *[8];
    for (int i = 0; i < 8; i++)
    {
        field[i] = new Button * [8];
    }

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {

            //("x: " + std::to_string(x) + " y " + std::to_string(y));
            np[x][y].setString(y_to_ch(x)+std::to_string(y+1));
            np[x][y].setFont(*font); // font is a sf::Font
            np[x][y].setCharacterSize(15);
            np[x][y].setFillColor(sf::Color::Black);
            np[x][y].setStyle(sf::Text::Bold);
            np[x][y].setPosition(50 + (100 * x), 750 - (y * 100));//(50+(100*x), 50 + (y * 100));
            //std::cout << np.getPosition().x << '\n';
            field[x][y] = new Button(kaf[x][y], np[x][y]);

            move_weeb[x][y].setTexture(movie_tex);
            move_weeb[x][y].setPosition(sf::Vector2f(50 + (x * 100), 750 - (100 * y)));

            if (board.get_piece(x, y) != nullptr)
            {
                pieces[x][y].setTexture(*get_piece_txt(board.get_piece(x, y)));
                pieces[x][y].setPosition(sf::Vector2f(50 + (x * 100), 750 - (100 * y)));
            }
        }
    }

    checked.x = -1;
    checked.y = -1;

    sf::RectangleShape rectex;
	sf::Text textex;

    rectex.setSize(sf::Vector2f(150.f, 50.f));  // Szerokość 200px, wysokość 50px
    rectex.setFillColor(sf::Color::Blue);  // Kolor przycisku
    rectex.setPosition(850, 150);  // Pozycja przycisku w oknie

        // Ustawienia tekstu
    textex.setFont(*font);
    textex.setString("EXIT");  // Ustaw tekst
    textex.setCharacterSize(24);  // Rozmiar tekstu
    textex.setFillColor(sf::Color::White);  // Kolor tekstu
    textex.setPosition(
            850 + (rectex.getSize().x - textex.getLocalBounds().width) / 2,  // Wyrównanie tekstu w poziomie
            150 + (rectex.getSize().y - textex.getLocalBounds().height) / 2  // Wyrównanie tekstu w pionie
		);

    exit = new Button(rectex,textex);
    exit->rect.setSize(sf::Vector2f(70.f, 30.f)); 
}

void Board_screen::play(sf::RenderWindow& w, Actions basic_events, char s[2])
{
    side[1] = s[0]; // bialy
    side[0] = s[1]; //czarny
    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Hand);
    bool koniec=0;

    clockk.start();

    while (true)
    {
        w.setMouseCursor(cursor);

        sf::Event event;
        // window.pollEvent(event);

        while (w.pollEvent(event))
        {
            //akt bier


            //std::cout << "EVENT borad cren\n";
            basic_events(event, w);
            //std::cout << "pressed przed\n";
            if (event.type == sf::Event::MouseButtonPressed)
            {
                std::cout << "pressed po\n";
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for (int y = 0; y < 8; y++)
                    {
                        // if aktualna strona gry != gracz -> break 
                        // board.round % 2
                        if ((this->side[board.get_round()%2] == 'C')||koniec==1)
                        {
                            break;
                        }

                        for (int x = 0; x < 8; x++)
                        {
                            field[x][y]->chState(w);
                            //std::cout << field[x][y]->getstate();// x HALOOOO y \n";
                            if (field[x][y]->getstate() == "pressed") 
                            {
                                pressed.x = x;
                                pressed.y = y;

                                /*for (int y1 = 0; y1 < 8; y1++)
                                {
                                    for (int x1 = 0; x1 < 8; x1++)
                                    {
                                        possible_movie[x1][y1] = false;
                                    }
                                }*/

                                if ((board.get_possible_move(pressed.x,pressed.y)==true)&&(checked.x!=-1)) {
                                    //std::cout<<pressed.x<<" "<<checked.x<<'\n';
                                    board.move(checked.x, checked.y, pressed.x, pressed.y);
                                    pieces[x][y].setTexture(*get_piece_txt(board.get_piece(x, y)));
                                    pieces[x][y].setPosition(sf::Vector2f(50 + (x * 100), 750 - (100 * y)));
                                    move_weeb[checked.x][checked.y].setTexture(movie_tex);
                                    checked.x = -1;
                                    checked.y = -1;

                                    y = 8;

                                    board.reset_possible_moves();
                                    //board.next_round();
                                    //std::cout<<"mat "<<board.mat()<<board.get_round()<<'\n';
                                    clockk.switchPlayer();

                                    for(int i=0;i<8;i++)
                                    {
                                        for(int j=0;j<8;j++)
                                        {
                                            if(board.get_piece(i,j)!=nullptr)
                                            {
                                            pieces[i][j].setTexture(*get_piece_txt(board.get_piece(i, j)));
                                            pieces[i][j].setPosition(sf::Vector2f(50 + (i * 100), 750 - (100 * j)));
                                            }
                                        }
                                    }

                                
                                    if(board.mat()==1)
                                    {
                                        koniec=1;
                                        clockk.stop();
                                    }
                                    break;
                                    //move
                                    //break
                                }

                                board.reset_possible_moves();

                                if ((pressed == checked)||(board.get_piece(pressed.x,pressed.y)==nullptr)||
                                    (board.get_piece(pressed.x, pressed.y)->get_side() == board.get_round() % 2))
                                {
                                    move_weeb[checked.x][checked.y].setTexture(movie_tex);
                                    checked.x = -1;
                                    checked.y = -1;
                                    y = 8;
                                    break;
                                }

                                if (checked.x != -1) { move_weeb[checked.x][checked.y].setTexture(movie_tex); }// if to zabezp 
                                //przed 1 razem, nadaj poprzedniemu standard tekst

                                checked.x = x;
                                checked.y = y;

                                move_weeb[x][y].setTexture(pressed_tex);
                                
                                board.set_possible_moves(pressed.x, pressed.y);//x , y
        
                                

                                //std::cout << std::to_string(x)+" "+std::to_string(y);

                                // Tutaj funkcja ustawienie na movie_weeb mo\BFliwe ruchy czyli possible_movies()
                                // funkcja zedytuje possible movie [8][8] na 1(ruch) lub 0(brak mozliwosci ruchu)
                                // potem przy wykonianu ruchu, sprawdza czy na miejscu byla bierka i dokonuje bicia
                                //
                                //possible_movie[x][y + 1] = true;
                            }
                        }
                    }
                    //std::cout << "the right button was pressed" << std::endl;
                    //std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    //std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    //std::cout<<"stat\n";
                    //exit.rect.setPosition(sf::Vector2f(850.f, 150.f));
                    exit->chState(w);
                    //std::cout<<exit.getstate()<<" stat\n";
                    //exit.gets();
                    //std::cout<<"clear3\n";
                    if(exit->getstate()=="pressed")
                    {
                        std::cout<<"exit\n";
                        return;
                    }
                    //std::cout<<"clear2\n";
                }
            }
            //klikniecia na kafelki
        }
        //std::cout<<"clear1\n";
        w.clear();
        //std::cout<<"clear\n";
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                field[x][y]->display(w);
                if (board.get_piece(x, y) != nullptr) 
                {
                    //std::cout << board.get_piece(x,y)->get_type();
                    w.draw(pieces[x][y]);
                }
                

                
            }
        }
        //std::cout << "hoj\n";

        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                if (board.get_possible_move(x,y) == true)
                {
                    w.draw(move_weeb[x][y]);
                }
                else if (sf::Vector2i(x,y) == checked)
                {
                    w.draw(move_weeb[x][y]);
                }
            }
        }
        //std::cout<<"weeb\n";
        //Button tet("abccc",500,500);
        //tet.display(w);
        clockk.update();
        clockk.draw(w);
        //std::cout<<"clock\n";

        exit->Button::display(w);
        if(koniec==1)mat_o.display(w);

        w.display();
        
        if ((this->side[board.get_round()%2]=='C')&&koniec!=1)
        {
            Bot bo;

            int* inp = bo.make_move(this->board,3);
            //std::cout<<inp[0];
            pieces[inp[2]][inp[3]].setTexture(*get_piece_txt(board.get_piece(inp[2], inp[3])));
            pieces[inp[2]][inp[3]].setPosition(sf::Vector2f(50 + (inp[2] * 100), 750 - (100 * inp[3])));
            move_weeb[inp[0]][inp[1]].setTexture(movie_tex);
            //std::cout<<"usadg2\n";
            //this->board.next_round();
            //delete[] inp;

            clockk.switchPlayer();
            board.reset_possible_moves();
            if(board.mat()==1)
            {
                koniec=1;
                clockk.stop();
            }
        }

        
    }
}

char Board_screen::y_to_ch(int y)
{
    switch (y)
    {
        case 0:
            return 'a';
            break;
        case 1:
            return 'b';
            break;
        case 2:
            return 'c';
            break;
        case 3:
            return 'd';
            break;
        case 4:
            return 'e';
            break;
        case 5:
            return 'f';
            break;
        case 6:
            return 'g';
            break;
        case 7:
            return 'h';
            break;

    }
return ' ';
}
