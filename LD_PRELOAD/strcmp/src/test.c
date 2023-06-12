#include "stdlib.h"
#include "stdio.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char * a = "lescats";
    if (strcmp(a, "flag{PwniiiLeChat}") == 0) {
        printf("Wow it is equal\n");
    }
    return 0;
}
