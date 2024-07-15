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
void setup_back_row(int i, int color);
void init_database();
void copy_str_array(char str[8][ART_LENGTH], char tocopy[8][ART_LENGTH]);
void replace_blank_white(char toReplace[ART_LENGTH]);
void replace_white_blank(char toReplace[ART_LENGTH]);
void make_move(int from, int to);
void get_move();
bool valid_user_input(char in[5]);

typedef struct{
    int color;
    char ptype;
    int position;
    char acsiiArt[8][ART_LENGTH];
}pieces;

typedef struct{
    int color;
}board;

// global vars
extern pieces * board_data[64]; // collection of 64 board structs 
extern board * empty_board[64]; // for checking color of area a piece landed on
               
                                    