
#include "chess_art.h"
#include "chess.h"
/*

To deal with pieces on different colored slotes of board
if the color is white replace every empty slot in the string
with a 0 before printing

*/

pieces *board_data[64];
board *empty_board[64];
int king_location;

void chess_init(bool flip){
    init_database();

    if(flip)
        flip_board();
        
    print_board();



}
/*
int main(){
    init_database();
    print_board();
    int * tmp = malloc(sizeof(int)*2);

    while(true){
        get_move(tmp);
        if(is_move_valid(tmp[0], tmp[1], true)){
            make_move(tmp[0], tmp[1]);
            board_data[tmp[1]]->moved = true;
            print_board();
        }
        else{
            puts("Invalid move");
        }
    }
    
}
*/

