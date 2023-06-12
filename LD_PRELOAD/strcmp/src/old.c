#include "stdlib.h"
#include "stdio.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    printf("===================[%s]==================\n", argv[0]);
    FILE * fp;
    printf("A printf before open\n");
    fp = fopen("./main.c","r");
    printf("A printf after open\n --> FILE * fd = %p\n", fp);
    char a[20];
    char b[20];
    strcpy(a, "whaaaaaaaa");
    printf("addr %p : \"%s\"\n", &a, a);
    strcpy(b, "heheheh");
    printf("addr %p : \"%s\"\n", &b, b);
    if (strcmp(a, b) == 0) {
        printf("Wow it is equal\n");
    }
    return 0;
}
