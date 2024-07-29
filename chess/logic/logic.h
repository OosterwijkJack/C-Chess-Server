#pragma once
#include "chess.h"

void get_piece_p_moves(int from, char ptype, int * out);
//void raytrace_move(int from, int to, int * out);
bool move_kills_king(int to, bool color);
void trace_up_down(int from, int * out, int * index);
void trace_left_right(int from, int *out, int * index);
void trace_diagonals(int from, int * out, int * index);
bool check_space(int space, int *index, int * out);
void raytrace_move(int from, int * moves);