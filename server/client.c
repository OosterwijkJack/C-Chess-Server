#include <client.h>

int create_client_socket()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
 
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    memset(&servaddr, 0, sizeof(servaddr));
    
    // get host ip from text file
    FILE * ptr;
    char buff[14];
    ptr = fopen("Host IP Addr.txt", "r");

    fgets(buff, sizeof(buff), ptr);
    buff[strlen(buff)] = '\0'; // remove new line


    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(buff);
    servaddr.sin_port = htons(PORT);
 
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        puts("connection with the server failed...");
        puts("Make sure you entered a valid ip address...");
        exit(0);
    }
    else
        puts("connected to the server..");
 
    // function for chat
    return sockfd;
 
    // close the socket
}


void close_client_socket(int sockfd){
    printf("Closing socket: %i\n",sockfd );
    close(sockfd);
}