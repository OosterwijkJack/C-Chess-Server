#include <chess.h>
/*

To deal with pieces on different colored slotes of board
if the color is white replace every empty slot in the string
with a 0 before printing

*/

pieces * board_data[64]; // collect of 64 board structs
board * empty_board[64]; // for checking color of area a piece landed on


void print_board();
void setup_back_row(int i, int color);
void init_database();

int main(void){
    init_database();

    for(int i = 0; i < 64; i++){
        if(board_data[i])
            printf("%i ",board_data[i]->ptype);
        if((i+1) % 8 == 0){
            printf("\n");
        }
    }
    
}

void init_database(){
    // dependent of (i//8)  and j 
    bool alt;
    setup_back_row(0, BLACK);
    setup_back_row(56, WHITE);

    for(int i = 0; i < 64; i++){
        // setup tiles
        empty_board[i] = malloc(sizeof(board));
        if(i % 2 == 0){
            if(alt)
                empty_board[i]->color = WHITE;
            else
                empty_board[i]->color = BLACK;
        }
        else{
            if(alt)
                empty_board[i]->color = BLACK;
            else
                empty_board[i]->color = WHITE;
        }

        if((i+1) % 8 == 0) // change order each row to form checker pattern
            alt = !alt;
        

        if(i >= 16 && i < 48){
            // make memory space for empty slots pieces may land on
            board_data[i] = malloc(sizeof(board));
            board_data[i]->position=i;
        }
        else if(i > 7 && i < 16){ // pawns at top of board
            board_data[i] = malloc(sizeof(pieces));
            board_data[i]->position = i;
            board_data[i]->ptype = PAWN;
            board_data[i]->color = BLACK;
        }
        else if(i > 47 && i < 56){ // pawns bottom of board
            board_data[i] = malloc(sizeof(pieces));
            board_data[i]->position = i;
            board_data[i]->ptype = PAWN;
            board_data[i]->color = WHITE;
        }
    }
}

void setup_back_row(int i, int color){
    
    char piece_table[] = {ROOK,HORSE,BISHOP,QUEEN,KING, BISHOP, HORSE,ROOK};
    int tmp = i;
    for(; i < tmp+8; i++){
        board_data[i] = malloc(sizeof(pieces));

        board_data[i]->color = color;
        board_data[i]->position = i;
        board_data[i]->ptype = piece_table[i-tmp];
    }
}

void print_board(){
    
}
