#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <vector>
#include <string>
#include <ctype.h>
#include <sstream>
#include <iostream>
#include <sys/stat.h>
#include <getopt.h>
#include <regex>
#include <string.h>
#include <string>
#include <stdarg.h>
#include <dlfcn.h>
using namespace std;

//struct DIR;

bool permission(const char *path){
    return true;
}
int chmod(const char *path, mode_t mode) {
    auto fnptr = NULL; /* function pointer */
    void *handle;
    if(fnptr == NULL) {
        handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            fnptr = reinterpret_cast<int (*)(const char *, mode_t)>(dlsym(handle, "chmod"));
    }
    if(fnptr != NULL)
        fprintf(stderr, "real uid = %d\n", fnptr(path, mode));
    dlclose(handle);
    return 0;
}
//DIR* opendir(const char *name){
//    if(!permission(name)){
//        printf("[sandbox] opendir: access to / is not allowed");
//    }
//}

