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

typedef struct{
    int color;
    char ptype;
    int position;
    char acsiiArt[8][ART_LENGTH];
}pieces;

typedef struct{
    int color;
}board;


               
                                    