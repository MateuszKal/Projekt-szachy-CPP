#ifndef bot_h
#define bot_h

#include <unordered_map>
#include "Board.h"

class Bot
{
private:
    float evaluate_position(Board &board);



    float minimax(Board &board, int depth, bool is_maximizing_player);

public:
    int* make_move(Board &board, int depth);
};

#endif