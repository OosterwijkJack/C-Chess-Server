#include <print.h>


void print_board(){
    system("clear");
    int current_row = 0;
    int art_index = 0;
    int index;
    for(int i = 0; i < 64; i++){

        if((i+1) % 4 == 0 && art_index != 7)
            printf(" %i ", 8-current_row);
        else
            printf("   ");

        for(int j = 0; j < 8; j++){ // prints one whole row of ascii art (which is of size 8)
            index = (current_row*8) + j; 
            if(board_data[index]->ptype){ // if there is a piece in that area
                
                if(empty_board[index]->color == WHITE){
                    replace_blank_white(board_data[index]->acsiiArt[art_index]); // replaces blank space in art  with 0 to keep up board pattern
                }
                printf(board_data[index]->acsiiArt[art_index]); // print ascii art (partially)
                replace_white_blank(board_data[index]->acsiiArt[art_index]);
            }
            else{
                if(empty_board[index]->color == WHITE)
                    printf(blankWhiteStr[art_index]);
                else
                    printf(blankBlackStr[art_index]);
                
            }
       }
       art_index++;
       printf("\n");
       if((i+1)%8 == 0 && i != 0){
        current_row++;
        art_index = 0;
       }
    }

    // print A-H at bottom of board
    printf("\n");
    for(int j = 0; j < 8; j++){
        printf("           %c    ", 'A'+j); 
       }
    printf("\n");
}

void replace_blank_white(char toReplace[ART_LENGTH]){

    for(int j = 0 ; j < strlen(toReplace); j++){
        if(toReplace[j] == ' '){
            toReplace[j] = '0';
        }
    }
}
void replace_white_blank(char toReplace[ART_LENGTH]){

    for(int j = 0 ; j < strlen(toReplace); j++){
        if(toReplace[j] == '0'){
            toReplace[j] = ' ';
        }
    }
}