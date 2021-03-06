#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void generate(char *buffer){
    bzero(buffer,256);
    fgets(buffer,255,stdin);
}

int main(int argc,char *argv[]){
    char server_message[256] = "You are now connected to the server";
    char end[4] = "END";
    char server_response[256];
    int socketfd,client;    // create a socket descriptor
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
    struct sockaddr_in client_address;
    int cli_add_len = sizeof(client_address);
    client = accept(socketfd,(struct sockaddr *)&client_address,&cli_add_len);
    
    //send the message
    send(client,server_message,sizeof(server_message),0);
    
    int pid = fork();
    if(pid < 0 ){
        perror("fork error\n");
        exit(1);
    }
    else if(pid == 0){
        while(1){
            //printf("In child\n");
            generate(server_message);
            send(client,server_message,sizeof(server_message),0);
            printf("Message sent to client\n");
        }
    }
    else{
        while(1){
        //receiving client message
        bzero(server_response,256);
        recv(client,&server_response,sizeof(server_response),0);
        printf("The Client sent the data:%s\n",server_response);
        if(strcmp(server_response,end)==0){
            return 0;
        }
        bzero(server_response,256);
        char server_ackg[256] = "Got your message!";
        send(client,server_ackg,sizeof(server_ackg),0);
        }
    }
    
    return 0;
}