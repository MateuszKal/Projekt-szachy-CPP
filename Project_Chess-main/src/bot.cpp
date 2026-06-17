#include "Bot.h"

float Bot::evaluate_position(Board &board)
    {
        std::unordered_map<char, int> piece_values = {
            {'p', 1}, // Pionek
            {'R', 5}, // Wieża
            {'N', 3}, // Skoczek
            {'B', 3}, // Goniec
            {'Q', 9}, // Królowa
            {'K', 0}  // Król (nie oceniamy, bo nie możemy go stracić)
        };

        float field_values[8][8] = {
            {0,0,0,0,0,0,0,0},
            {0,0.5,0.5,0.5,0.5,0.5,0.5,0},
            {0.25,0.75,0.75,0.75,0.75,0.75,0.75,0.25},
            {0.25,0.75,1,1.25,1.25,1,0.75,0.25},
            {0.25,0.75,1,1.25,1.25,1,0.75,0.25},
            {0.25,0.75,0.75,0.75,0.75,0.75,0.75,0.25},
            {0,0.5,0.5,0.5,0.5,0.5,0.5,0},
            {0,0,0,0,0,0,0,0}
        };

        float evaluation = 0;

        // Przechodzimy przez całą planszę
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                Piece* piece = board.get_piece(x, y);
                if (piece != nullptr) {
                    char type = piece->get_type(); // Zakładamy, że Piece ma metodę get_type() zwracającą typ figury
                    int value = piece_values[type];

                    // Jeśli figura jest białą, dodajemy jej wartość, jeśli czarną, odejmujemy
                    if (piece->is_white()) { // Zakładamy metodę is_white() w Piece
                        evaluation += value+field_values[x][y];
                    } else {
                        evaluation -= value+field_values[x][y];
                    }
                }
            }
        }
        //std::cout<<evaluation<<'\n';
        return evaluation;
    }

float Bot::minimax(Board &board, int depth, bool is_maximizing_player)
    {
        //std::cout<<"minmax\n";
        //std::cout<<"Minmax "<<is_maximizing_player<<'\n';
        if (depth == 0 || board.mat()) {//|| board.mat()
            if(board.mat()==1) return board.get_round()%2 ? -10000 : 10000; //????
            return evaluate_position(board); // Oceniamy pozycję, jeśli osiągniemy maksymalną głębokość lub mat
        }

        float best_value = is_maximizing_player ? -10000 : 10000; // min max ?
        // Sprawdzamy możliwe ruchy
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                if (board.get_piece(x, y) != nullptr && board.get_piece(x, y)->is_white() == is_maximizing_player) {
                    board.reset_possible_moves();
                    board.set_possible_moves(x, y);

                    for (int xm = 0; xm < 8; ++xm) {
                        for (int ym = 0; ym < 8; ++ym) {
                            if (board.get_possible_move(xm, ym)) {
                                // Przechowujemy stan planszy
                                //std::cout<<"board\n";
                                Board new_board = board;
                                //std::cout<<x<<" "<<y<<" "<<xm<<" "<<ym<<'\n';
                                new_board.move(x, y, xm, ym); // Wykonujemy ruch
                                //std::cout<<"board end\n";
                                //std::cout<<x+1<<" "<<y+1<<" | "<<xm+1<<" "<<ym+1<<'\n';
                                float current_value = minimax(new_board, depth - 1, !is_maximizing_player);// min max ?

                                if (is_maximizing_player) {
                                    best_value = std::max(best_value, current_value); // Maksymalizujemy wynik
                                } else {
                                    best_value = std::min(best_value, current_value); // Minimalizujemy wynik
                                }
                                //std::cout<<best_value;
                            }
                        }
                    }
                }
            }
        }
        //std::cout<<best_value<<"minmax end\n";
        return best_value;
    }

    int* Bot::make_move(Board &board, int depth)
    {
        //std::cout<<"make move\n";
        float best_value = 10000; // min max ?
        int* best_move = new int[4];
        best_move[0] = -1;

        // Przechodzimy przez wszystkie możliwe ruchy bota
        for (int x = 0; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                if (board.get_piece(x, y) != nullptr && !board.get_piece(x, y)->is_white()) {
                    board.reset_possible_moves();
                    board.set_possible_moves(x, y);

                    for (int xm = 0; xm < 8; ++xm) {
                        for (int ym = 0; ym < 8; ++ym) {
                            if (board.get_possible_move(xm, ym)) 
                            {
                                // Przechowujemy stan planszy
                                //std::cout<<x<<" "<<y<<" "<<xm<<" "<<ym<<" przed min max\n";
                                Board new_board = board;
                                new_board.move(x, y, xm, ym); // Wykonujemy ruch
                                //std::cout<<"dd\n";
                                float move_value = minimax(new_board, depth - 1, true); // Tura przeciwnika (minimalizowanie)// min max ?
                                //std::cout<<"mv value"<<move_value<<'\n';
                                if (move_value < best_value || best_move[0]==-1) {
                                    best_value = move_value;
                                    //best_move = {x, y, xm, ym};
                                    //std::cout<<"zapis\n";
                                    best_move[0] = x;
                                    best_move[1] = y;
                                    best_move[2] = xm;
                                    best_move[3] = ym; // Zapamiętujemy najlepszy ruch
                                }
                            }
                        }
                    }
                    //board.reset_possible_moves();
                }
            }
        }
        //std::cout<<"movep\n";
        // Wykonanie najlepszego ruchu
        //std::cout<<"wypisz ruch\n";

        std::cout<<best_move[0]<<" " <<best_move[1]<<" " <<best_move[2]<<" "<< best_move[3]<<'\n';

        board.move(best_move[0], best_move[1], best_move[2], best_move[3]);
        //std::cout<<"movepo\n";
        //int* out = best_move;
        board.reset_possible_moves();
        

    //std::cout<<out[0];
    //std::cout<<out[1];
    //std::cout<<out[2];
        //std::cout<<out[3];
        //std::cout<<"ahsbad\n";

        //std::cout<<"make move end\n";
        return best_move;
    }
