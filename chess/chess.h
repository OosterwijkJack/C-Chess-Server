#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "chess_art.h"
#include <string.h>

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
void make_move(int from, int to);

typedef struct{
    int color;
    char ptype;
    int position;
    char acsiiArt[8][ART_LENGTH];
}pieces;

typedef struct{
    int color;
}board;


               
                                    