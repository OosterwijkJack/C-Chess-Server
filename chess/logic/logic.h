#pragma once
#include "chess.h"

void get_piece_p_moves(int from, char ptype, int * out);
//void raytrace_move(int from, int to, int * out);
bool is_stale_mate();
bool is_check_mate();
bool move_kills_king(int to);
void trace_up_down(int from, int * out);
bool check_space(int space, int *index, int * out);