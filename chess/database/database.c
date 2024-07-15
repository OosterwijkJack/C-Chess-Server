#include <database.h>

void init_database(){
    // dependent of (i//8)  and j 
    bool alt;
    setup_back_row(0, BLACK); // important pieces
    setup_back_row(56, WHITE);

    for(int i = 0; i < 64; i++){
        // setup tiles
        empty_board[i] = malloc(sizeof(board));
        // creates pattern
        if((i+1) % 2 == 0){
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
            board_data[i] = malloc(sizeof(pieces));
            board_data[i]->position=i;
        }
        else if(i > 7 && i < 16){ // pawns at top of board
            board_data[i] = malloc(sizeof(pieces));
            board_data[i]->position = i;
            board_data[i]->ptype = PAWN;
            board_data[i]->color = BLACK;
            board_data[i]->moved = false;
            copy_str_array(bPawn, board_data[i]->acsiiArt);
        }
        else if(i > 47 && i < 56){ // pawns bottom of board
            board_data[i] = malloc(sizeof(pieces));
            board_data[i]->position = i;
            board_data[i]->ptype = PAWN;
            board_data[i]->color = WHITE;
            board_data[i]->moved = false;
            copy_str_array(wPawn,board_data[i]->acsiiArt);  
        }

    }

}

void setup_back_row(int i, int color){
    
    char piece_table[] = {ROOK,HORSE,BISHOP,QUEEN,KING, BISHOP, HORSE,ROOK};
    char (*ascii_table_black[8])[8][ART_LENGTH] = {&bRook, &bHorse, &bBishop, &bQueen, &bKing, &bBishop, &bHorse, &bRook}; // an array of memory locations to 2d arrays.
    char (*ascii_table_white[8])[8][ART_LENGTH] = {&wRook, &wHorse, &wBishop, &wQueen, &wKing, &wBishop, &wHorse, &wRook};
    int tmp = i;
    for(; i < tmp+8; i++){
        board_data[i] = malloc(sizeof(pieces));

        board_data[i]->color = color;
        board_data[i]->position = i;
        board_data[i]->ptype = piece_table[i-tmp];
        if(color == WHITE)
            copy_str_array(*ascii_table_white[i-tmp], board_data[i]->acsiiArt);
        else
            copy_str_array(*ascii_table_black[i-tmp], board_data[i]->acsiiArt);
    }
}

void copy_str_array(char str[8][ART_LENGTH], char tocopy[8][ART_LENGTH]){

    for(int i = 0; i < 8; i ++){
        strcpy(tocopy[i], str[i]);
    }

}