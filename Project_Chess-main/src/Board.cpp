#include "Board.h"
#include <iostream>

Board::~Board()
{
	delete[] piece;
	delete[] possible_move;
	//std::cout<<"destruktor\n";
}

Board::Board(const Board &other)
    {
		//std::cout<<"aa\n";
        // Kopiowanie wartości prostych
        round = other.round;
        check = other.check;

        // Kopiowanie dynamicznej tablicy `piece` (Piece***)
        piece = new Piece**[8];
        for (int i = 0; i < 8; ++i) {
            piece[i] = new Piece*[8];
            for (int j = 0; j < 8; ++j) {
                // Jeśli w oryginale jest figura, kopiujemy ją (zakładamy, że Piece ma konstruktor kopiujący)
                if (other.piece[i][j] != nullptr) 
				{
					if(other.piece[i][j]->get_type()=='p') piece[i][j] = new Pawn(other.piece[i][j]->x, other.piece[i][j]->y, other.piece[i][j]->side);//(*other.piece[i][j]);
					else if(other.piece[i][j]->get_type()=='K') piece[i][j] = new King(other.piece[i][j]->x, other.piece[i][j]->y, other.piece[i][j]->side);
					else if(other.piece[i][j]->get_type()=='N') piece[i][j] = new Knight(other.piece[i][j]->x, other.piece[i][j]->y, other.piece[i][j]->side);
					else if(other.piece[i][j]->get_type()=='B') piece[i][j] = new Bishop(other.piece[i][j]->x, other.piece[i][j]->y, other.piece[i][j]->side);
					else if(other.piece[i][j]->get_type()=='Q') piece[i][j] = new Queen(other.piece[i][j]->x, other.piece[i][j]->y, other.piece[i][j]->side);
					else if(other.piece[i][j]->get_type()=='R') piece[i][j] = new Rock(other.piece[i][j]->x, other.piece[i][j]->y, other.piece[i][j]->side);
				} else {
                    piece[i][j] = nullptr;
                }
            }
        }
		//std::cout<<"bb\n";
        // Kopiowanie tablicy `possible_move`
        possible_move = new bool*[8];
        for (int i = 0; i < 8; ++i) {
            possible_move[i] = new bool[8];
            for (int j = 0; j < 8; ++j) {
                possible_move[i][j] = other.possible_move[i][j];
            }
        }
		//std::cout<<"cc\n";
    }

Board::Board()
{
	possible_move = new bool* [8];
	piece = new Piece * *[8];
	for (int i = 0; i < 8; i++) 
	{
		piece[i] = new Piece * [8];
		possible_move[i] = new bool[8];
		for (int x = 0; x < 8; x++)
		{
			piece[i][x] = nullptr;
			possible_move[i][x] = false;
		}
	}
	// Tu ulozuc plansze
	
	piece[7][0] = new Rock(7, 0, 0);
	//piece[0][0]->set_x(0);
	//piece[0][0]->set_y(0);
	piece[1][0] = new Knight(1, 0, 0);
	piece[2][0] = new Bishop(2,0,0);
	piece[3][0] = new Queen(3,0,0);
	piece[4][0] = new King(4,0,0);
	piece[5][0] = new Bishop(5,0,0);
	piece[6][0] = new Knight(6,0,0);
	piece[0][0] = new Rock(0,0,0);
	//piece[7][0]->set_x(7);
	//piece[7][0]->set_y(0);

	for (int i = 0; i < 8; i++) 
	{ 
		piece[i][1] = new Pawn(i, 1, 0);
		/*piece[i][2]->set_x(i);
		piece[i][2]->set_y(2);*/
	}

	piece[0][7] = new Rock(0, 7, 1);
	piece[1][7] = new Knight(1, 7, 1);
	piece[2][7] = new Bishop(2, 7, 1);
	piece[3][7] = new Queen(3, 7, 1);
	piece[4][7] = new King(4, 7, 1);
	piece[5][7] = new Bishop(5, 7, 1);
	piece[6][7] = new Knight(6, 7, 1);
	piece[7][7] = new Rock(7, 7, 1);

	for (int i = 0; i < 8; i++) { piece[i][6] = new Pawn(i, 6, 1); }

	//piece[0][6] = new Bishop(0, 6, 0);
	//piece[0][2] = nullptr;

	
	round = 1;

	//std::cout<<p->get_type();
}

Piece* Board::get_piece(int x, int y)
{
	return piece[x][y];
}

int Board::get_round()
{
	return round;
}

void Board::set_possible_moves(int x, int y)
{
	get_piece(x, y)->possible_move(piece, possible_move);
}

void Board::reset_possible_moves()
{
	for (int i = 0; i < 8; i++)
	{
		for (int x = 0; x < 8; x++)
		{		
			possible_move[i][x] = false;
		}
	}
}

bool Board::get_possible_move(int x, int y)
{
	return possible_move[x][y];
}

void Board::move(int x, int y, int xm, int ym)
{
	//std::cout<<"Board::move\n";
	if (piece[xm][ym] != nullptr)
	{
		delete piece[xm][ym];
	}
	
	piece[xm][ym] = piece[x][y];
	
	piece[xm][ym]->set_x(xm);
	
	piece[xm][ym]->set_y(ym);
	
	piece[x][y] = nullptr;
	
	//std::cout<<"SZACH "<<piece[xm][ym]->check_check(this->piece)<<'\n';
	//this->check = piece[xm][ym]->check_check(this->piece);

	// Z ODSŁONY DODAC ???
	//std::cout<<"type "<<piece[xm][ym]->get_type()<<'\n';
	if (piece[xm][ym]->get_type() == 'p') 
	{ // Jeśli to pionek
        if (piece[xm][ym]->side == 0 && ym == 7) { // Biały pionek na 7. wierszu
            delete piece[xm][ym];
            piece[xm][ym] = new Queen(xm, ym, 0); // Promocja na białą hetman
        } else if (piece[xm][ym]->side == 1 && ym == 0) { // Czarny pionek na 0. wierszu
            delete piece[xm][ym];
            piece[xm][ym] = new Queen(xm, ym, 1); // Promocja na czarną hetman
        }

		//std::cout<<xm<<" "<<ym<<" ruch \n";

		if((xm==Piece::ben)&&(ym==2))
		{
			//std::cout<<"DELETE BB\n";
			delete piece[Piece::ben][3];
			piece[Piece::ben][3] = nullptr;
		}
		if((xm==Piece::wen)&&(ym==5))
		{
			//std::cout<<"DELETE BB\n";
			delete piece[Piece::wen][4];
			piece[Piece::wen][4] = nullptr;
		}


		Piece::ben = -1;
		Piece::wen = -1;
		if((ym == 3)&&(y==1))
		{
			Piece::ben = x;
			//std::cout<<Piece::ben<<"benn\n";
		}
		if((ym == 4)&&(y==6))
		{
			Piece::wen = x;
			//std::cout<<Piece::ben<<"benn\n";
		}

    }
	std::cout<<"typ "<<piece[xm][ym]->get_type()<<'\n';
	if (piece[xm][ym]->get_type() == 'K') 
	{
		std::cout<<"rosz??\n";
		if((x==4)&&(xm==2)&&(y==0))
		{
			//std::cout<<"rosz";
			piece[3][0] = piece[0][0];
			piece[3][0]->set_x(3);
			piece[0][0] = nullptr;
		}
		else if((x==4)&&(xm==6)&&(y==0))
		{
			//std::cout<<"rosz";
			piece[5][0] = piece[7][0];
			piece[5][0]->set_x(5);
			piece[7][0] = nullptr;
		}
		else if((x==4)&&(xm==2)&&(y==7))
		{
			//std::cout<<"rosz";
			std::cout<<"roszcz";
			piece[3][7] = piece[0][7];
			piece[3][7]->set_x(3);
			piece[0][7] = nullptr;
		}
		else if((x==4)&&(xm==6)&&(y==7))
		{
			//std::cout<<"rosz";
			std::cout<<"roszcz";
			piece[5][7] = piece[7][7];
			piece[5][7]->set_x(5);
			piece[7][7] = nullptr;
		}

	}

	next_round();
}

void Board::next_round()
{
	round++;
}

bool Board::mat()
{
	int xk, yk;
	bool che=0; 




	for (int x=0;x<8;x++)
	{
		for (int y=0;y<8;y++)
		{ 
			if(piece[x][y]==nullptr) continue;
			if((piece[x][y]->type=='K')&&((get_round()%2)!=piece[x][y]->side)) // znajdz krola, tego sam kolor co ruch
			{
				xk = x;
				yk = y;
			}

			if((get_round()%2)==piece[x][y]->side)// znajdz atak na krola
			{	
				che = piece[x][y]->check_check(piece);
				//std::cout<<"che"<<che<<'\n';
				if(che==1) break;
			}
		}
		if(che==1) break;
	}

	reset_possible_moves();

	if(che == 0) return 0;
	//std::cout<<che;
	for (int x=0;x<8;x++)
	{
		for (int y=0;y<8;y++)
		{
			if(piece[x][y]==nullptr) continue;
			if(get_round()%2!=piece[x][y]->side)// wszystkie bierki krórych krol jest atakowany
			{
				set_possible_moves(x,y);

				for (int xc=0;xc<8;xc++)
				{
					for (int yc=0;yc<8;yc++)
					{
						if(possible_move[xc][yc]==1)
						{
							//std::cout<<"poss";
							reset_possible_moves();
							return 0;
						}
					}
				}
			}
		}
	}

	reset_possible_moves();
	return 1;
}