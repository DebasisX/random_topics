#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> // network libraries.
#include <sys/socket.h> // network libraries.

#define PORT 8080 // use any port of your choice. 
#define BUFFER_SIZE 1024

int main() { // initialize.
    int server, sock;
    struct sockaddr_in address;
    int option = 1;
    int len_address = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    // creating sock FD.
    if ((server = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        printf("sock failed to initialize");
        exit(1);
    }
    
    // attaching sock to the port.
    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option))) {
        printf("failed to attach");
        close(server);
        exit(1);
    }
    // initializing the address.
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // binding sock to the network address and port
    if (bind(server, (struct sockaddr *)&address, sizeof(address)) < 0) {
        printf("failed to bind");
        close(server);
        exit(1);	
    }
    
    // listening for incoming connections.
    if (listen(server, 3) < 0) {
        printf("listen");
        close(server);
        exit(1);
    }
    
    printf("server listening on port %d\n", PORT);
    
    // accepting connections.
        if ((sock = accept(server, (struct sockaddr *)&address, (socklen_t*)&len_address)) < 0) {
        printf("accept");
        close(server);
        exit(1);
    }
    
    // read HTTP request.
   	read(sock, buffer, sizeof(buffer));
    printf("received message: %s\n", buffer);
    
    // sending HTTP response.
    char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nHi Debasis!\n"; // normal HTTP response. 
    send(sock, response, strlen(response), 0);
    printf("response sent to client\n");
    
    // closing sock after use.
    close(sock);
    close(server);
    
    return 0;
}
