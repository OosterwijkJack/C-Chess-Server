#include <server.h>

int sockfd;
char cmessage[MAX];

int create_server_socket(void){
    int connfd, len;
    struct sockaddr_in servaddr, cli; 

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // udp socket that will be used with an ipv4 address. 0 defines default protocol
    
    // sockfd being socket file descriptior as sockets are treated the same as files
    if(sockfd == -1){
        puts("Socket creation failed...");
        exit(0);
    }

    else
        puts("Socket created..");

    memset(&servaddr, 0, sizeof(servaddr)); // set servaddr to zero
    

    servaddr.sin_family = AF_INET; // ipv4
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //accept any incoming ip address
    servaddr.sin_port = htons(PORT); // htons converts byte order to big-endian meaning most sig byte is stored at smallest memory address

    if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0){ // bind socket and servaddr the socket is the endpoint for processing the information and the address is where information is sent
        puts("Socket binding failed...");
        exit(0);
    }
    
    else
        puts("Socket binded succesfully...");

    if((listen(sockfd, 2))!= 0){ // socket is now listening for traffic. System can only queue up to two connections before it starts refusing new connections
        puts("Listen failed...");
        exit(0);
    }
    else
        puts("Server listening...");
    
    len = sizeof(cli); // sizeof client buffer
    connfd = accept(sockfd, (SA*)&cli, &len);  // accept data sent from client. len is sent as pointer so it can be rewriten to the actual size of the data
    if(connfd < 0){
        puts("Server accept faile...");
        exit(0);
    }
    else 
        puts("Server accept the client...");

    return connfd;

}

char* client_communicate(int connfd){ // talk to client
    char buff[MAX];
    memset(cmessage, 0, MAX);

    int n;

    for(int i = 0; i < 1; i++){
        memset(&buff, 0, MAX);

        read(connfd, buff, sizeof(buff));
        strcpy(cmessage, buff);

        printf("To client: ");

        memset(&buff, 0, MAX);
        n=0;

        while((buff[n++] = getchar()) != '\n') // write to buffer until newline char
            ;
        
        write(connfd, buff, sizeof(buff)); // writing to connector file descriptor 

        return cmessage;
    }
}

void close_server_socket(){
    printf("Closing socket: %i\n",sockfd );
    close(sockfd);
}