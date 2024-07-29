#include "logic.h"

bool is_move_valid(int from, int to, bool color){

    if(!(board_data[from]->ptype)){
        puts("Not an existing piece");
        return false;
    }

    int * piece_moves = malloc(sizeof(int)*33); 
    raytrace_move(from, piece_moves);
    bool valid = false;
    for(int i = 0 ; i < 64; i ++){

        if(piece_moves[i] == -1) // acts as terminating character
            break;
            
        // check if move will put king in danger
        int *list = malloc(sizeof(int) * 32);

        if(piece_moves[i] == to){ // that move can be made
            if(!(board_data[to]->ptype && board_data[from]->color == board_data[to]->color && (color == board_data[from]->color))){
                valid = true;
                break;
            }
        }
    }
    // free data
    free(piece_moves);
    return valid;
}


// find what moves the piece can make checking for pieces in the way
void raytrace_move(int from, int * moves){
    int index = 0;
    char ptype = board_data[from]->ptype;

    if(ptype == 'p'){
        if(from >= 8){
            if(!board_data[from-8]->ptype){
                moves[index] = from -8; // space ahead`
                index++;
            }
        }
            
        if(!board_data[from]->moved && from >= 16){
            if(!board_data[from-16]->ptype){
                moves[index] = from - 16; // two spaces ahead
                index++;
            }
        }

        if(from >= 9){
            if(!(from% 8 == 0) && board_data[from-9]->ptype){
            moves[index] = from-9; // piece diag to pawn
            index++;
            }
        }

        if(from >= 7){
            if(!(from%8 == 7) && board_data[from-7]->ptype){
                moves[index] = from-7; // piece diag to pawn
                index++;
            }
        }
        moves[index] = -1;
        return;
    } 
    

    // rook
    else if(ptype == 'r'){
        trace_left_right(from, moves, &index);
        trace_up_down(from, moves, &index);
    }
    // horse
    else if(ptype == 'h'){

        if(!((from)%8==0) && from + 15 <= 63){ // down two left one cant be far left of board
            moves[index] = from + 15;
            index++;
        }

        if(!(from%8 == 7) && from + 17 <=63){ // down two right one cant be far right of board
            moves[index] = from + 17; 
            index++;
        }

        if(!(from % 8 >= 5) && from + 10 <= 63){// right two down one
            moves[index] = from + 10;
            index++;
        }

        if((from % 8) >= 2 && from + 6 <= 63){ // left two down one
            moves[index] = from + 6; // left two down one
            index++;
        }

        if(!(from%8 == 7) && from-15 > 0){
            moves[index] = from - 15;
            index++;
        }

        if(!(from%8 == 0) && from-17 > 0){
            moves[index] = from - 17;
            index++;
        }

        if((from%8 >= 2) && from-10 > 0){
            moves[index] = from - 10;
            index++;
        }

        if((from%8 <= 5) && from-6 > 0){
            moves[index] = from - 6;
            index++;
        }
        moves[index] = -1;
    }
    // bishop
    else if(ptype == 'b'){
        trace_diagonals(from, moves, &index);
    }
    // queen
    else if(ptype == 'q'){
        trace_left_right(from, moves, &index);
        trace_up_down(from, moves, &index);
        trace_diagonals(from, moves, &index);
        moves[index] = -1;
    }
    // king
    else if (ptype == 'k'){
        if (from % 8 != 0) { // left
            moves[index] = from - 1;
            index++;
        }
        if (from % 8 != 7 && from + 1 <= 63) { // right
            moves[index] = from + 1;
            index++;
        }
        if (from + 8 <= 63) { // up
            moves[index] = from + 8;
            index++;
        }
        if (from - 8 >= 0) { // down
            moves[index] = from - 8;
            index++;
        }
        if (from % 8 != 7 && from + 9 <= 63) { // diag right up
            moves[index] = from + 9;
            index++;
        }
        if (from % 8 != 0 && from - 9 >= 0) { // diag left down
            moves[index] = from - 9;
            index++;
        }
        if (from % 8 != 0 && from + 7 <= 63) { // diag left up
            moves[index] = from + 7;
            index++;
        }
        if (from % 8 != 7 && from - 7 >= 0) { // diag right down
            moves[index] = from - 7;
            index++;
        }
        moves[index] = -1;
    }
}


void trace_diagonals(int from, int * out, int * index){
    bool first = true;
    for(int i = from +9; i < 64; i+=9 ){

        if(from % 8 == 7){
            if(first){
                first = false;
                continue;
            }
            else{
                out[*index] = i;
                *index+=1;
                break;
            }
        }

        if(!check_space(i, index, out))
            break;
        first = false;
    }
    first  = true;
    for(int i = from -9; i > 0; i-=9 ){

        if(from%8 == 0){
            if(first)
                continue;
            else{
                out[*index] = i;
                *index+=1;
                break;
            }
        }

        if(!check_space(i, index, out))
            break;
        first = false;
    }
    first = true;
     for(int i = from +7; i < 64; i+=7 ){

        if(from%8 == 0){
            if(first)
                continue;
            else{
                out[*index] = i;
                *index+=1;
                break;
            }
        }

        if(!check_space(i, index, out))
            break;
        first = false;
    }
    first = true;
    for(int i = from -7; i > 0; i-=7 ){

        if(from % 8 == 7){
            if(first)
                continue;
            else{
                out[*index] = i;
                *index+=1;
                break;
            }
        }

        if(!check_space(i, index, out))
            break;
        first = false;
    }
    out[*index] = -1;
};

void trace_up_down(int from, int * out, int * index){
    for(int i = from+8; i < 64; i += 8){ // starting at space one ahead going up
        if(!check_space(i,index, out)){
            break;
        }
    }
    for(int i = from-8; i < 64; i -= 8){ // starting at space one below going down
        if(!check_space(i,index, out)){
            break;
        }
    }
    out[*index] = -1;
}

void trace_left_right(int from, int *out, int * index){
    for(int i = from+1; i < 8+ from; i++){
        if(i > ((((int)from/8)+1)*8)-1 || i < ((int)from/8)*8){
            break;
        }
        if(!check_space(i, index, out))
            break;
    }
    for(int i = from-1; i < 8+from; i--){
        if(i > ((((int)from/8)+1)*8)-1 || i < ((int)from/8)*8){
            break;
        }
        if(!check_space(i, index, out))
            break;
    }
    out[*index] = -1;
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

bool is_stale_mate(bool color){
    bool take = false;

    int * tmp = malloc(sizeof(int)*10);
    raytrace_move(board_data[king_location], tmp);

    if(!piece_can_be_taken(king_location, color)){
        for(int i = 0; tmp[i] != -1; i++){
            if(piece_can_be_taken(tmp[i], color))
                take=true;
        }
        if(!take)
            return true;
    }
    return false;
}

// returns true if the move the player is making will cause the king to be taken
bool piece_can_be_taken(int to, bool color){
    int *tmp = malloc(sizeof(int)*33);

    for(int i = 0 ; i < 64; i ++){

        if(board_data[i]->color == color) // dont check own pieces
            continue;

        raytrace_move(i, tmp);
        int index = 0 ;

        while(tmp[index++] != -1){ // if other pieces have oppertunity to take king return true
        // keep track of who can take king to check if it can be taken later
            if(tmp[index] == to){
                return true;
            }
        memset(tmp, 0, sizeof(tmp));
        }
    }
    free(tmp);
    return false;
}
