#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ART_LENGTH 50

#define WHITE 0
#define BLACK 1

#define PAWN 'p'
#define ROOK 'r'
#define HORSE 'h'
#define BISHOP 'b'
#define QUEEN 'q'
#define KING 'k'

void print_board();
void init_database();
void make_move(int from, int to);
void get_move();
bool is_move_valid(int from, int to, bool color);
bool is_game_over();
void flip_board();
void chess_init(bool flip);
void copy_str_array(char str[8][ART_LENGTH], char tocopy[8][ART_LENGTH]);

typedef struct{
    int color;
    char ptype;
    int position;
    char acsiiArt[8][ART_LENGTH];
    bool moved; // only for pawns
}pieces;

typedef struct{
    int color;
}board;

// global vars
extern pieces * board_data[64]; // collection of 64 board structs 
extern board * empty_board[64]; // for checking color of area a piece landed on
               
                                    