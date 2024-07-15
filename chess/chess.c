
#include "chess_art.h"
#include "chess.h"
/*

To deal with pieces on different colored slotes of board
if the color is white replace every empty slot in the string
with a 0 before printing

*/

pieces *board_data[64];
board *empty_board[64];

int main(void){
    init_database();
    make_move(59, 47);
    print_board();

    int * piece_moves = malloc(sizeof(int)*28);
    raytrace_move(47, 'p', piece_moves);


    /*

    int * tmp = malloc(sizeof(int)*2);

    while(true){
        get_move(tmp);
        make_move(tmp[0], tmp[1]);
        print_board();
    }
    */

}

