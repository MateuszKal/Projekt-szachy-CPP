#ifndef piece_h
#define piece_h

#include <iostream>

class Piece
{
public:


	int x;
	int y;
	char type = 'n';
	int movies = 0;
	bool side; // 0 = white ||| 1 = blac
	bool check_move_collision_and_check(int xm, int ym, Piece*** board, bool mov[8][8], bool* check);// used in
	//void move to set every single example, returns 1 if field is nullptr
	//virtual void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr) = 0;// 
	//sets move 
	//table taking into account colisions and/or sets check

public:
	static int wen;
	static int ben;
	static bool white_king_moved, black_king_moved, white_rook_right_moved;
	static bool white_rook_left_moved, black_rook_right_moved, black_rook_left_moved;

	bool is_white();
	bool check_check(Piece*** board); // check if piece is checking

	Piece(int x_, int y_, bool side_) : x(x_), y(y_), side(side_){}
	virtual void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr) = 0;

	void possible_move(Piece*** board, bool** possible_mov);// based on table made with void 
	//move it confirms move corectness taking into account checks
	virtual bool possible_capture(int x, int y, Piece*** board) = 0;// @up
	//virtual char get_type() = 0;
	//virtual void Promotion ->>>>>>>>>>>>dodaj!! czyli zmiana type!!!!
	void set_x(int x_);
	void set_y(int y_);
	int get_movies();
	char get_type();
	bool get_side();
};

class Pawn :public Piece
{
	//static const char type = 'P';
	//void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);
public:
	Pawn(int x_, int y_, bool side_) : Piece(x_, y_, side_) {
		type = 'p';
	}
	Pawn(const Piece &other);

	void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);
	//void possible_move(Piece*** board, bool** possible_mov); // w agrumencie wskaznik do tablicy, z ustawieniem bierek ---+++
	bool possible_capture(int x, int y, Piece*** board);// @up
};

class Knight :public Piece
{
	//static const char type = 'K';
	//void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);
public:
	//void move(bool mov[8][8], Piece*** board, bool* check = nullptr);
	Knight(int x_, int y_, bool side_) : Piece(x_, y_, side_) {
		type = 'N';
	}
	Knight(const Piece &other);
	void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);
	//void possible_move(Piece*** board, bool** possible_mov); // w agrumencie wskaznik do tablicy, z ustawieniem bierek ---+++
	bool possible_capture(int x, int y, Piece*** board);// @up
};

class Bishop :public Piece
{
	//static const char type = 'B';
	//void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);
public:
	//void move(bool mov[8][8], Piece*** board, bool* check = nullptr);

	Bishop(int x_, int y_, bool side_) : Piece(x_, y_, side_) {
		type = 'B';
	}
	Bishop(const Piece &other);
	void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);
	//void possible_move(Piece*** board, bool** pissible_mov); // w agrumencie wskaznik do tablicy, z ustawieniem bierek ---+++
	bool possible_capture(int x, int y, Piece*** board);// @up
};

class Rock :public Piece
{
	//static const char type = 'B';
	//void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);
public:
	//void move(bool mov[8][8], Piece*** board, bool* check = nullptr);

	Rock(int x_, int y_, bool side_) : Piece(x_, y_, side_) {
		type = 'R';
	}
	Rock(const Piece &other);
	void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);

	//void possible_move(Piece*** board, bool** pissible_mov); // w agrumencie wskaznik do tablicy, z ustawieniem bierek ---+++
	bool possible_capture(int x, int y, Piece*** board);// @up

};

class Queen :public Piece
{
	//static const char type = 'B';
	//void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);
public:
	//void move(bool mov[8][8], Piece*** board, bool* check = nullptr);

	Queen(int x_, int y_, bool side_) : Piece(x_, y_, side_) {
		type = 'Q';
	}
	Queen(const Piece &other);
	void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);
	//void possible_move(Piece*** board, bool** pissible_mov); // w agrumencie wskaznik do tablicy, z ustawieniem bierek ---+++
	bool possible_capture(int x, int y, Piece*** board);// @up
};

class King :public Piece
{
	//static const char type = 'B';
	//void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);
public:
	//void move(bool mov[8][8], Piece*** board, bool* check = nullptr);

	King(int x_, int y_, bool side_) : Piece(x_, y_, side_) {
		type = 'K';
	}
	King(const Piece &other);
	void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);
	//void possible_move(Piece*** board, bool** pissible_mov); // w agrumencie wskaznik do tablicy, z ustawieniem bierek ---+++
	bool possible_capture(int x, int y, Piece*** board);// @up
};

class None :public Piece
{
	//static const char type = 'B';
	//void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);
public:
	//void move(bool mov[8][8], Piece*** board, bool* check = nullptr);
	void set_collision_table(bool mov[8][8], Piece*** board, bool* check = nullptr);
	//void possible_move(Piece*** board, bool** possible_mov);// w agrumencie wskaznik do tablicy, z ustawieniem bierek ---+++
	bool possible_capture(int x, int y, Piece*** board);// @up
};


#endif