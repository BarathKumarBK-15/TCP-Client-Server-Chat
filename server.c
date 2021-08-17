#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define PORT 4455


int main() {
    int server_socket;
    struct sockaddr_in server_address;

    int client_socket;
    struct sockaddr_in client_address;

    char buffer[1024];
    socklen_t addr_size;

    server_socket = socket(PF_INET, SOCK_STREAM, 0);

    if(server_socket == -1) {
        printf("Socket Connection Failed!!\n");
        exit(0);
    } else {
        printf("Socket Connection Established!!\n");
    }

    bzero(&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) != 0) {
        printf("Socket Binding Failed!!\n");
        exit(0);
    } else {
        printf("Socket Binding Established!!\n");
    }

    if(listen(server_socket, 5) != 0) {
        printf("Listening Failed!!\n");
        exit(0);
    } else {
        printf("Server waiting for Clients\n");
    }

    addr_size = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr*)&client_address, &addr_size);

    if(client_socket < 0) {
        printf("Failed to Accept Clients!!\n");
        exit(0);
    } else {
        printf("Client Accepted!!\n");
    }
    
    char name[100];
    int i=0;
    printf("Enter your name : ");
    while((name[i++] = getchar()) != '\n');
    int len = i;

    while(1>0) {
        bzero(buffer, 1024);
        recv(client_socket, buffer, sizeof(buffer), 0);

        if(strncmp("exit", buffer, 4) == 0) {
            printf("The client has left!!\n");
            break;
        }

        printf("%s", buffer);

        bzero(buffer, 1024);
        int n=0,j=0;

        printf("Enter Message to client: ");
        while((buffer[n++] = getchar()) != '\n');

        buffer[n-1] = ',';
        for(j=0; j<len; j++) {
            buffer[j+n] = name[j];
        }

        send(client_socket, buffer, sizeof(buffer), 0);

        if(strncmp("exit", buffer, 4) == 0) {
            printf("You have closed the Server!!\n");
            break;
        }
    }

    return 0;
}