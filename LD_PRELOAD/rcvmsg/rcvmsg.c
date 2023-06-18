#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/socket.h>

int orig_recvmsg(int sockfd, struct msghdr *msg, int flags);
int recvmsg(int sockfd, struct msghdr *msg, int flags)
{
    int orig_recvmsg = dlsym(RTLD_NEXT, "recvmsg");
}

// S: Sysfs=/devices/pci0000:00/0000:00:14.0/usb1/1-8/1-8:1.0/0003:3233:6301.0004/input/input9
