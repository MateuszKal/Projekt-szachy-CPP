#ifndef board_h
#define board_h


#include "Pieces.h"


class Board
{
	Piece*** piece;
	int round;
	bool** possible_move;
	bool check;

public:
	~Board();
	Board();
	Board(const Board &other);

	//void move_piece(sf::Vector2i p);
	Piece* get_piece(int x, int y);
	int get_round();
	void set_possible_moves(int x, int y);
	void reset_possible_moves();
	bool get_possible_move(int x, int y);

	void move(int x, int y, int xm, int ym);
	void next_round();

	bool mat();

	// void move( x, y, x2, y2) sprawdza czy sie da move(zarkes ruch�w w sytuacji), czy po tym m�j kr�l ma szacha , 
	// bicie, promocja, szach, mat
	// i jedze jak nie to odmowa
	// przy sprawdzaniu skopiuj piece(statycznie) i sprawdz na tym potem kopia nba oryginal, inaczej 
	//beda problemy lub zrob backup odpowiednich bierek
};

#endif