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
void errmsg(const char funcname[], const char path[]){
    fprintf(stderr, "[sandbox] %s: access to %s is not allowed\n", funcname, path);
}
bool permission(const char *path){
    return strcmp(getenv("PWD"), path)==0;
}
int chmod(const char *path, mode_t mode) {
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    auto fnptr = reinterpret_cast<int (*)(const char *, mode_t)>(dlsym(handle, "chmod"));/* function pointer */
        
    if(fnptr){
	if (!permission(path)){
	    errmsg("chmod", path);
	    return -1;
	} else{
	    int ret = fnptr(path, mode);
	    dlclose(handle);
	    return ret;
	}
    }

    return 0;
}

