#include <stdio.h>
#include <stdlib.h>

int strcmp(const char *s1, const char *s2) //prototype of strcmp() from man 
{
    printf("strcmp() will be hooked\n");
    printf("first argument: %s\n", s1);    //priting first argument from prototype
    printf("second argument: %s\n", s2);   //priting second argument from prototype

}

//////////////////////////////////////////////////////////////
//gcc strcmp.c -o strcmp.so -fPIC -shared -ldl -D_GNU_SOURCE//
//               LD_PRELOAD=./strcmp.so ./file              //
//////////////////////////////////////////////////////////////