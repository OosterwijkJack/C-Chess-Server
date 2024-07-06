#include <client.h>

char hmessage[MAX];

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
 
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
 
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        puts("connection with the server failed...");
        exit(0);
    }
    else
        puts("connected to the server..");
 
    // function for chat
    return sockfd;
 
    // close the socket
}

char * server_communicate(int sockfd) // talk to server
{
    char buff[MAX];
    int n;
    for(int i = 0; i < 1; i++){
        memset(&buff, 0, MAX);
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        memset(&buff, 0, MAX);
        read(sockfd, buff, sizeof(buff));
        strcpy(hmessage, buff);
        return hmessage;
    }
}

void close_client_socket(int sockfd){
    printf("Closing socket: %i\n",sockfd );
    close(sockfd);
}