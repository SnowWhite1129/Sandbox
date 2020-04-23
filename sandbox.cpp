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
void errmsg(const char funcname[]){
    // path
    fprintf(stderr, "[sandbox] %s: access to / is not allowed\n", funcname);
}
//bool permission(const char *path){
//    return strcmp(getenv("PWD"), path)==0;
//}
bool permission(){
    return true;
}
#define arg(...) __VA_ARGS__

#define FUNC(type, func_name, args, args2) \
type func_name(args) {                     \
    void *handle = dlopen("libc.so.6", RTLD_LAZY); \
    auto lib_##fnptr = reinterpret_cast<int (*)(const char *, mode_t)>(dlsym(handle, #func_name));/* function pointer */ \
    fprintf(stderr, "Injected\n");          \
                                            \
    if(lib_##fnptr){                        \
        if (!permission()){                 \
            errmsg(#func_name);             \
        } else{                             \
            int ret = lib_##fnptr(args2);   \
            dlclose(handle);                \
        }                                   \
    }                                       \
}

FUNC(int, chdir, arg(const char *path), arg(path))

FUNC(int, chmod, arg(char* path, mode_t mode), arg(path, mode))

FUNC(int, chown, arg(const char *pathname, uid_t owner, gid_t group), arg(pathname, owner, group))

FUNC(int, creat, arg(const char *pathname, mode_t mode), arg(pathname, mode))

FUNC(struct FILE*, arg(const char *pathname, const char *mode), arg(pathname, mode))

FUNC(int, link, arg(const char *oldpath, const char *newpath), arg(oldpath, newpath))

FUNC(int, mkdir, arg(const char *pathname, mode_t mode), arg(pathname, mode))
//open
//openat
//opendir
//readlink
//remove
//rename
//rmdir
//__xstat
//symlink
//unlink

//execl
//execle
//execlp
//execv
//execve
//execvp
//system

//int chmod(const char *path, mode_t mode) {
//    void *handle = dlopen("libc.so.6", RTLD_LAZY);
//    auto fnptr = reinterpret_cast<int (*)(const char *, mode_t)>(dlsym(handle, "chmod"));/* function pointer */
//
//    fprintf(stderr, "Injected chmod\n");
//
//    if(fnptr){
//        if (!permission(path)){
//            errmsg("chmod", path);
//            return -1;
//        } else{
//            int ret = fnptr(path, mode);
//            dlclose(handle);
//            return ret;
//        }
//    }
//    return 0;
//}

