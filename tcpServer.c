#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void createChat(int); // function to data transfer with client

int main(int argc,char *argv[]){
    // create a socket descriptor
    int socketfd,client; 
    int portno;
    if(argc < 2){
        perror("Not enough arguments");
        printf("Usage:./tcpServer <port number>\n");
        exit(1);
    }
    portno = atoi(argv[1]);

    //creating a server socket
    socketfd = socket(AF_INET,SOCK_STREAM,0);
    if (socketfd < 0){
         perror("ERROR opening socket");
         exit(1);
    }

    //create server socket address
    struct sockaddr_in server_address;
    server_address.sin_family  = AF_INET;
    server_address.sin_port = htons(portno);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //Bind socket with specified IP and port
    bind(socketfd,(struct sockaddr *)&server_address,sizeof(server_address));

    //listen for connection
    listen(socketfd,5);
    
    //create a client socket address and accept connection
    int i=0;
    int pid;
    struct sockaddr_in client_address[20];
    int cli_add_len = sizeof(client_address[0]);
    while(1){
        client = accept(socketfd,(struct sockaddr *)&client_address,&cli_add_len);
        if(client < 0){
            perror("Error on accept\n");
            break;
        }
        pid = fork();
        if (pid < 0 ){
            perror("Fork Error\n");
            exit(1);
        }

        else if(pid ==0){   // child process
            close(socketfd);
            createChat(client);
            exit(0);
        }
        else{
            close(client);
        }
        
    }
    
    return 0;
}

void createChat(int client){
    char server_message[256] = "You are now connected to the server";
    char server_ackg[256] = "Got your message!";
    char server_response[256];

    //send the message

    send(client,server_message,sizeof(server_message),0);

    //receiving client message
    bzero(server_response,256);
    recv(client,&server_response,sizeof(server_response),0);
    printf("The Client sent the data:%s\n",server_response);
    bzero(server_response,256);

    //sending acknowledge to client

    send(client,server_ackg,sizeof(server_ackg),0);
    
}