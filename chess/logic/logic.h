#pragma once
#include "chess.h"

void get_piece_p_moves(int from, char ptype, int * out);
int raytrace_move(int from, int to);
bool is_stale_mate();
bool is_check_mate();
bool move_kills_king(int to);