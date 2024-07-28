#include <stdio.h>
#include "client.h"
#include "server.h"
#include "tools.h"
#include <stdbool.h>
#include <signal.h>
#include "chess.h"
#include "chess_art.h"

#define HOST 1
#define CLIENT 0
bool serverType = NULL;

void communicate(int sockfd, int * tmp, char buff[MAX]);
void receive_move(char buff[MAX], int * tmp, int sockfd);
void send_move(char buff[MAX], int * tmp, int sockfd);
void parse_message(int* msg, char * buff, int chgPiece);
void parse_response(char* resp, int* out, int sockfd);
void exit_call(int sockfd);
void pawn_end_of_board(int pos, char newp);

int main(int argc, char* argv[]){
    // argv checks for assigning server/client for communication
    signal(SIGINT, exit_call);
    if(argc != 2){
        puts("Usage: ./main {client/host}");
        exit(0);
    }
    
    if(strcmp(argv[1], "host") == 0){
        serverType = HOST;
    }
    else if(strcmp(argv[1], "client") == 0){
        serverType = CLIENT;
    }
    else{
        puts("Invalid arg. Input should be either \"server\" or \"client\"");
        exit(0);
    }

    // setup server
    int sockfd = 0;
    if(serverType == HOST){
        sockfd = create_server_socket();
    }
    else{
        sockfd = create_client_socket();
    }

    chess_init(serverType);

    char buff[MAX];
    int * tmp = malloc(sizeof(int)*2);
    while(true){
        communicate(sockfd, tmp, buff);
    }
}
/*

Create seperate functions for reading and writing so data can be retrieved as wanted

*/
void communicate(int sockfd, int * tmp, char buff[MAX]){
    if(serverType == HOST){
        receive_move(buff, tmp, sockfd);
        send_move(buff, tmp, sockfd);
        
    }
    else{
        send_move(buff, tmp, sockfd);
        receive_move(buff, tmp, sockfd);
    }
}

void send_move(char buff[MAX], int * tmp, int sockfd){
    memset(buff, 0, MAX);
    memset(tmp, 0, sizeof(int)*2);
    // make move
    while(true){
        get_move(tmp);
        if(is_move_valid(tmp[0], tmp[1], serverType))
            break;
        else{
            puts("Invalid move...");
        }
    }

    // from (tmp[0]) to (tmp[1])
    printf("%i %i\n", tmp[0], tmp[1]);

    make_move(tmp[0], tmp[1]);

    // if pawn travelled entire board
    int chgPiece = 0;
    if(board_data[tmp[1]]->ptype == 'p' && tmp[1] <= 7){
        char newp = (char)0; 
        printf("\n\t\tRook (r)\tHorse (h)\tBishop(b)\tQueen (q)\n");
        printf("Enter new piece: ");

        while(newp != 'r' && newp != 'h' && newp != 'b' && newp != 'q') // get input until valid
            newp = getchar();

        pawn_end_of_board(tmp[1], newp);
        chgPiece = tmp[1];
    }


    board_data[tmp[1]]->moved = true;

    print_board();
    parse_message(tmp, buff, chgPiece);

    puts(buff);
    write_message(sockfd, buff, MAX);

}
void receive_move(char buff[MAX], int * tmp, int sockfd){
    // clear vars
    memset(buff, 0, MAX);
    memset(tmp, 0, sizeof(int)*2);

    read_message(sockfd, buff, MAX);
    parse_response(buff, tmp, sockfd);

    printf("%i %i\n", 63-tmp[0], 63-tmp[1]);

    make_move(63-tmp[0], 63-tmp[1]); // 63 - move to because board is mirrored

    if(tmp[2] != 0)
        pawn_end_of_board(tmp[1], (char)tmp[2]);

    print_board();
}

void parse_message(int* msg, char * buff, int chgPiece){
    if(chgPiece == 0)
        sprintf(buff, "%i %i\0", msg[0], msg[1]);
    else{
        sprintf(buff, "%i %i %i\0", msg[0], msg[1], chgPiece);
    }
}
void parse_response(char* resp, int* out, int sockfd){
    printf("%i\n", strlen(resp));

    if (strlen(resp) == 0){ // when user enters ctrl + c to exit it sends an empty response back, which will cause seg fault if not dealt with
        puts(serverType == HOST ? "Client disconnected": "Host disconnected");
        exit_call(sockfd);
    }

    char * token = strtok(resp, " ");

    out[0] = atoi(token);
    out[1] = atoi(strtok(NULL, " ")); // continue tokenization
    
    token = strtok(NULL, " ");
    if(token != NULL)
        out[2] = (int)token[0];
    else
        out[2] = 0;
}

void exit_call(int sockfd){
    if(serverType == HOST){
        close_server_socket();
        puts("Host socket closed");
    }
    else{
        close_client_socket(sockfd);
        puts("Client socket closed");
    }
    exit(0);
}

void pawn_end_of_board(int pos, char newp){
    if(board_data[pos]->ptype == 'p' && pos <= 7){
        // edit piece
        if(newp == 'q'){
            board_data[pos]->ptype = 'q';
            if(board_data[pos]->color == WHITE)
                copy_str_array(wQueen, board_data[pos]->acsiiArt);
            else
                copy_str_array(bQueen, board_data[pos]->acsiiArt);

        }
        else if(newp == 'b'){
            board_data[pos]->ptype = 'b';
            if(board_data[pos]->color == WHITE)
                copy_str_array(wBishop, board_data[pos]->acsiiArt);
            else
                copy_str_array(bBishop, board_data[pos]->acsiiArt);

        }
        else if(newp == 'h'){
            board_data[pos]->ptype = 'h';
            if(board_data[pos]->color == WHITE)
                copy_str_array(wHorse, board_data[pos]->acsiiArt);
            else
                copy_str_array(bHorse, board_data[pos]->acsiiArt);
        }
        else if (newp == 'r'){
            board_data[pos]->ptype = 'r';
            if(board_data[pos]->color == WHITE)
                copy_str_array(wRook, board_data[pos]->acsiiArt);
            else
                copy_str_array(bRook, board_data[pos]->acsiiArt);

        }
        else{
            exit(1);
        }
    }
        
}