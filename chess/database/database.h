#pragma once
#include "chess_art.h"
#include "chess.h"

void copy_str_array(char str[8][ART_LENGTH], char tocopy[8][ART_LENGTH]);
void setup_back_row(int i, int color);