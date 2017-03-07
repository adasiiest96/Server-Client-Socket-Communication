#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void generate(char *buffer){
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
}
int main(int argc, char *argv[]){
    int socketfd; // create a socket descriptor
    int portno;
    int flag =0;
    char server_response[256];
    char end[4] = "END";
    if(argc < 2){
        perror("Not enough arguments");
        printf("Usage:./tcpClient <IP_address of Server> <port number>\n");
        exit(1);
    }
    portno = atoi(argv[1]);
    socketfd = socket(AF_INET,SOCK_STREAM,0);
    if (socketfd < 0){
         perror("ERROR opening socket");
         exit(1);
    }
    // specify address of the socket
    struct sockaddr_in server_address;
    server_address.sin_family  = AF_INET;
    server_address.sin_port = htons(portno);
    server_address.sin_addr.s_addr = INADDR_ANY; 
    if(connect(socketfd,(struct sockaddr *)&server_address,sizeof(server_address)) == -1){
        printf("There is an error in connection\n");
        exit(1);
    }//socket has been connected to the server & ready for send/recv
    printf("Connected With server\n");
    bzero(server_response,256);
    recv(socketfd,&server_response,sizeof(server_response),0);
    printf("%s\n",server_response);
    printf("hi\n");
    while(1){
        //Generate data to send the server
        generate(server_response);
        send(socketfd,server_response,sizeof(server_response),0);
        if(strcmp(server_response,end) ==0){
            flag = 1;
        }
        bzero(server_response,256);
    
        //receive server response
        recv(socketfd,&server_response,sizeof(server_response),0);
        
        //Printing out server response
        printf("The server sent the data:%s\n",server_response);
        if(flag == 1){
            return 0;
        }
        }
}
