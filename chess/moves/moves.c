
#include "moves.h"

void get_move(int * table){ // get and validate user input
    char fromb[5];
    memset(table, 0 , sizeof(table));
    printf("From: ");
    scanf("%4s", fromb);

    while (!valid_user_input(fromb)){
        printf("\nFrom:");
        memset(fromb, 0 , sizeof(fromb));
        scanf("%4s", fromb);
    }
    
    char tob[5];
    printf("To: ");
    scanf("%4s", tob);

    while(!valid_user_input(tob)){
        printf("\nTo:");
        memset(tob, 0 , sizeof(tob));
        scanf("%4s", tob);
    }
    
    int tmp = fromb[0] - 'A' ;
    table[0] = 64 - ((int)(fromb[1]-'0')*8) + tmp;

    tmp = tob[0] - 'A' ;
    table[1] = 64 - ((int)(tob[1] - '0')*8) + tmp;
}

bool valid_user_input(char in[5]){

    int len = strlen(in);

    if(len!=2){
        puts("Input is not 2 characters long");
        return false;
    }

    if(!(isalpha(in[0]))){ // must be a character
        puts("invalid input 0");
        return false;
    }

    if(!(isupper(in[0]))) // convert to uppercase
        in[0] = toupper(in[0]);

    if(!isdigit(in[1])){
        puts("invalid input 1");
        return false;
    }
    return true;

}
void make_move(int from, int to){ // take user input and make move
    // set new position and free old one
    pieces * tmp = board_data[to];
    board_data[to] = board_data[from];
    
    board_data[from] = malloc(sizeof(pieces));
    board_data[from]->position = from;
    board_data[from]->ptype = (char)0;

    if(tmp != NULL)
        free(tmp);

}

