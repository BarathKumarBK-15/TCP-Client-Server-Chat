#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define PORT 4455


int main() {
    int client_socket;
    struct sockaddr_in server_address;

    client_socket = socket(PF_INET, SOCK_STREAM, 0);

    if(client_socket == -1) {
        printf("Socket Connection Failed!!\n");
        exit(0);
    } else {
        printf("Socket Connection Established!!\n");
    }

    bzero(&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) != 0) {
        printf("Server Connection Failed!!\n");
        exit(0);
    } else {
        printf("Server Connection Established!!\n");
    }

    char buffer[1024];

    char name[100];
    int i=0;
    printf("Enter your name : ");
    while((name[i++] = getchar()) != '\n');
    int len = i;

    while(1>0) {
        bzero(buffer, 1024);
        int n=0,j=0;

        printf("Enter Message to Server: ");
        while((buffer[n++] = getchar()) != '\n');

        buffer[n-1] = ',';
        for(j=0; j<len; j++) {
            buffer[j+n] = name[j];
        }

        send(client_socket, buffer, sizeof(buffer), 0);

        if(strncmp("exit", buffer, 4) == 0) {
            printf("You have left the chat room!!\n");
            break;
        }

        bzero(buffer, 1024);
        recv(client_socket, buffer, sizeof(buffer), 0);

        if(strncmp("exit", buffer, 4) == 0) {
            printf("The server has been closed!!\n");
            break;
        }

        printf("%s", buffer);
    }

    return 0;
}