#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <cstdio>
enum command {Access, Exec};
static FILE* (*old_fopen)(const char *pathname, const char *mode) = nullptr;
static FILE* (*old_fopen64)(const char *pathname, const char *mode) = nullptr;

void errmsg(const char funcname[], const char path[], command cmd){
    if(!path){
	    printf("Error path\n");
    }
    FILE *fp;
    void *handle = dlopen("libc.so.6", RTLD_LAZY);
    if(old_fopen == nullptr) {
        if(handle != nullptr)
            old_fopen = reinterpret_cast<FILE* (*)(const char *, const char *)>(dlsym(handle, "fopen"));
    }
    if(old_fopen64 == nullptr) {
        if(handle != nullptr)
            old_fopen64 = reinterpret_cast<FILE* (*)(const char *, const char *)>(dlsym(handle, "fopen64"));
    }
    switch (cmd){
        case Access:
            if((fp = old_fopen("/dev/tty", "w")) == nullptr)
                fprintf(fp, "[sandbox] %s: access to %s is not allowed\n", funcname, path);
            break;
        case Exec:
            if((fp = old_fopen("/dev/tty", "w")) == nullptr)
                fprintf(fp, "[sandbox] %s(%s): not allowed\n", funcname, path);
            break;
    }
}
bool permission(const char path[], command cmd){
    if(cmd == Exec){
	    return false;
    }
    char abspath[1024], absbase[1024];
    realpath(getenv("BASEDIR"), absbase);
    if(path==nullptr){
	    printf("Path is null\n");
    }   
    if (realpath(path, abspath)){
        return strncmp(abspath, absbase, strlen(absbase))==0;
    } else{
        return false;
    }
}

#define arg(...) __VA_ARGS__

#define FUNC(type, func_name, args, args2, ec, path, cmd) \
type func_name(args) {                     \
    void *handle = dlopen("libc.so.6", RTLD_LAZY); \
    auto lib_##fnptr = reinterpret_cast<type (*)(args)>(dlsym(handle, #func_name));/* function pointer */ \
    				            \
    if(lib_##fnptr){                        \
        if (!permission(path, cmd)){        \
            errmsg(#func_name, path, cmd);  \
            return ec;                      \
        } else{                             \
            type ret = lib_##fnptr(args2);  \
            dlclose(handle);                \
            return ret;                     \
        }                                   \
    } else{				                    \
        fprintf(stderr, "Not found\n");     \
        return ec;			                \
    }	    				                \
}

#ifdef __cplusplus
extern "C"{
FUNC(int, chdir, arg(const char *path), arg(path), -1, path, Access)

FUNC(int, chmod, arg(char* path, mode_t mode), arg(path, mode), -1, path, Access)

FUNC(int, chown, arg(const char *pathname, uid_t owner, gid_t group), arg(pathname, owner, group), -1, pathname, Access)

FUNC(int, creat, arg(const char *pathname, mode_t mode), arg(pathname, mode), -1, pathname, Access)
FUNC(int, creat64, arg(const char *pathname, mode_t mode), arg(pathname, mode), -1, pathname, Access)

FUNC(FILE*, fopen, arg(const char *pathname, const char *mode), arg(pathname, mode), nullptr, pathname, Access)
FUNC(FILE*, fopen64, arg(const char *pathname, const char *mode), arg(pathname, mode), nullptr, pathname, Access)

FUNC(int, link, arg(const char *oldpath, const char *newpath), arg(oldpath, newpath), -1, newpath, Access)

FUNC(int, mkdir, arg(const char *pathname, mode_t mode), arg(pathname, mode), -1, pathname, Access)


FUNC(int, open, arg(const char *pathname, int flags, mode_t mode), arg(pathname, flags, mode), -1, pathname, Access)
FUNC(int, open64, arg(const char *pathname, int flags, mode_t mode), arg(pathname, flags, mode), -1, pathname, Access)

FUNC(int, openat, arg(int dirfd, const char *pathname, int flags, mode_t mode), arg(dirfd, pathname, flags, mode), -1, pathname, Access)
FUNC(int, openat64, arg(int dirfd, const char *pathname, int flags, mode_t mode), arg(dirfd, pathname, flags, mode), -1, pathname, Access)

FUNC(struct DIR*, opendir, arg(const char *name), arg(name), nullptr, name, Access)

FUNC(ssize_t , readlink, arg(const char *pathname, char *buf, size_t bufsiz), arg(pathname, buf, bufsiz), -1, pathname, Access)

FUNC(int, remove, arg(const char *pathname), arg(pathname), -1, pathname, Access)

FUNC(int, rename, arg(const char *oldpath, const char *newpath), arg(oldpath, newpath), -1, newpath, Access)

FUNC(int, rmdir, arg(const char *pathname), arg(pathname), -1, pathname, Access)

FUNC(int, __xstat, arg(int ver, const char *pathname, struct stat *statbuf), arg(ver, pathname, statbuf), -1, pathname, Access)
FUNC(int, __xstat64, arg(int ver, const char *pathname, struct stat *statbuf), arg(ver, pathname, statbuf), -1, pathname, Access)

FUNC(int, symlink, arg(const char *target, const char *linkpath), arg(target, linkpath), -1, linkpath, Access)

FUNC(int, unlink, arg(const char *pathname), arg(pathname), -1, pathname, Access)

FUNC(int, execl, arg(const char *path, const char *arg, ...), arg(path, arg), -1, path, Exec)

FUNC(int, execle, arg(const char *path, const char *arg, ...), arg(path, arg), -1, path, Exec)

FUNC(int, execlp, arg(const char *file, const char *arg, ...), arg(file, arg), -1, file, Exec)

FUNC(int, execv, arg(const char *path, char *const argv[]), arg(path, argv), -1, path, Exec)

FUNC(int, execve, arg(const char *pathname, char *const argv[], char *const envp[]), arg(pathname, argv, envp), -1, pathname, Exec)

FUNC(int, execvp, arg(const char *file, char *const argv[]), arg(file, argv), -1, file, Exec)

FUNC(int, system, arg(const char *command), arg(command), -1, command, Exec)

}
#endif
