#include "logic.h"

bool is_move_valid(int from, int to){

    if(!(board_data[from]->ptype)){
        puts("Not an existing piece");
        return false;
    }

    int * piece_moves = malloc(sizeof(int)*28); // 27 is most possible moves available to one piece at one time + space for -1
    //raytrace_move(from, to, piece_moves);
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

// find what moves the piece can make checking for pieces in the way
void raytrace_move(int from, char ptype){
    int * buff = malloc(sizeof(int)*28);
    trace_up_down(from, buff);

    for(int i = 0; i < 28;i++){
        if(buff[i] == -1)
            break;

        printf("%i\n", buff[i]);
    }
}

void trace_up_down(int from, int * out){
    int index = 0;
    for(int i = from+8; i < 64; i += 8){ // starting at space one ahead going up
        if(!check_space(i,&index, out)){
            break;
        }
    }
    for(int i = from-8; i < 64; i -= 8){ // starting at space one below going down
        if(!check_space(i,&index, out)){
            break;
        }
    }
    out[index] = -1;
}

void trace_left_right(int from, int *out){
    
}

bool check_space(int space, int *index, int * out){
    if(space > 63 || space < 0){ // check in bounds
        return false;
    }

    if(board_data[space]->ptype){ // met piece
        out[*index] = space;
        *index+=1;
        return false;
    }

    out[*index] = space;
    *index+=1;
    return true;
    
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