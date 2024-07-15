#include "logic.h"

bool is_move_valid(int from, int to){
    int * piece_moves = malloc(sizeof(int)*28); // 27 is most possible moves available to one piece at one time + space for -1
    get_piece_p_moves(from, to, piece_moves);
    bool valid = false;
    for(int i = 0 ; i < 64; i ++){
        
        if(piece_moves[i] == -1) // acts as terminating character
            break;

        if(piece_moves[i] == to){ // that move can be made
            valid = true;
            break;
        }
    }
    
    if (!valid){
        puts("That piece cant move like that");
        return false;
    }
}

bool is_game_over(){
    if(is_stale_mate() || is_check_mate())
        return true;
    return false;
}

// find what moves the piece can make disregarding other pieces being in the way
void get_piece_p_moves(int from, char ptype, int * out){

}

// returns valid moves a player can make taking into account other pieces in the path of a move
int raytrace_move(int from, int to){

}

// king cant make a valid move and not in immediate danger
bool is_stale_mate(){

}

// this will simply check if a king has died. I prefer being able to actually kill the King
// instead of the game just telling me I win (and its easier)
bool is_check_mate(){

}

// returns true if the move the player is making will kill the king
bool move_kills_king(int to){

}