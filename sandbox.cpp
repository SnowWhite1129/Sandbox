#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <cstdio>

enum command {Access, Exec};
void errmsg(const char funcname[], const char path[], command cmd){
    switch (cmd){
        case Access:
            fprintf(stderr, "[sandbox] %s: access to %s is not allowed\n", funcname, path);
            break;
        case Exec:
            fprintf(stderr, "[sandbox] %s(%s): not allowed\n", funcname, path);
            break;
    }
}
void errmsg(const char funcname[], const char path[], const char path2[], command cmd){
    switch (cmd){
        case Access:
            fprintf(stderr, "[sandbox] %s: access to %s or %s is not allowed\n", funcname, path, path2);
            break;
        case Exec:
            fprintf(stderr, "[sandbox] %s(%s): not allowed\n", funcname, path);
            break;
    }
}
bool permission(const char *path){
    char abspath[1024], absbase[1024];
    realpath(getenv("BASEDIR"), absbase);
    if (realpath(path, abspath)){
        return strncmp(abspath, absbase, strlen(abspath))==0;
    } else{
        return false;
    }
}
bool permission(const char *path, const char *path2){
    char abspath[1024], abspath2[1024], absbase[1024];
    realpath(getenv("BASEDIR"), absbase);
    if (realpath(path, abspath) && realpath(path2, abspath2)){
        return (strncmp(abspath, absbase, strlen(abspath))==0) && (strncmp(abspath2, absbase, strlen(abspath2))==0);
    } else{
        return false;
    }
}

#define arg(...) __VA_ARGS__

#define FUNC(type, func_name, args, args2, ec, path, cmd) \
type func_name(args) {                     \
    void *handle = dlopen("libc.so.6", RTLD_LAZY); \
    auto lib_##fnptr = reinterpret_cast<type (*)(args)>(dlsym(handle, #func_name));/* function pointer */ \
    fprintf(stderr, "Injected\n");          \
                                            \
    if(lib_##fnptr){                        \
        if (!permission(path)){             \
            errmsg(#func_name, path, cmd);  \
            return ec;                      \
        } else{                             \
            type ret = lib_##fnptr(args2);  \
            dlclose(handle);                \
            return ret;                     \
        }                                   \
    }                                       \
}
/*
FUNC(int, chdir, arg(const char *path), arg(path), -1, arg(path), Access)

FUNC(int, chmod, arg(char* path, mode_t mode), arg(path, mode), -1, arg(path), Access)

FUNC(int, chown, arg(const char *pathname, uid_t owner, gid_t group), arg(pathname, owner, group), -1, arg(pathname), Access)

FUNC(int, creat, arg(const char *pathname, mode_t mode), arg(pathname, mode), -1, arg(pathname), Access)
FUNC(int, creat64, arg(const char *pathname, mode_t mode), arg(pathname, mode), -1, arg(pathname), Access)

FUNC(FILE*, fopen, arg(const char *pathname, const char *mode), arg(pathname, mode), nullptr, arg(pathname), Access)
FUNC(FILE*, fopen64, arg(const char *pathname, const char *mode), arg(pathname, mode), nullptr, arg(pathname), Access)

FUNC(int, link, arg(const char *oldpath, const char *newpath), arg(oldpath, newpath), -1, arg(oldpath, newpath), Access)

FUNC(int, mkdir, arg(const char *pathname, mode_t mode), arg(pathname, mode), -1, arg(pathname), Access)

FUNC(int, open, arg(const char *pathname, int flags), arg(pathname, flags), -1, arg(pathname), Access)
FUNC(int, open64, arg(const char *pathname, int flags), arg(pathname, flags), -1, arg(pathname), Access)
FUNC(int, open, arg(const char *pathname, int flags, mode_t mode), arg(pathname, flags, mode), -1, arg(pathname), Access)
FUNC(int, open64, arg(const char *pathname, int flags, mode_t mode), arg(pathname, flags, mode), -1, arg(pathname), Access)

FUNC(int, openat, arg(int dirfd, const char *pathname, int flags), arg(dirfd, pathname, flags), -1, arg(pathname), Access)
FUNC(int, openat64, arg(int dirfd, const char *pathname, int flags), arg(dirfd, pathname, flags), -1, arg(pathname), Access)
FUNC(int, openat, arg(int dirfd, const char *pathname, int flags, mode_t mode), arg(dirfd, pathname, flags, mode), -1, arg(pathname), Access)
FUNC(int, openat64, arg(int dirfd, const char *pathname, int flags, mode_t mode), arg(dirfd, pathname, flags, mode), -1, arg(pathname), Access)

FUNC(struct DIR*, opendir, arg(const char *name), arg(name), nullptr, arg(name), Access)

FUNC(ssize_t , readlink, arg(const char *pathname, char *buf, size_t bufsiz), arg(pathname, buf, bufsiz), -1, arg(pathname), Access)

FUNC(int, remove, arg(const char *pathname), arg(pathname), -1, arg(pathname), Access)

FUNC(int, rename, arg(const char *oldpath, const char *newpath), arg(oldpath, newpath), -1, arg(oldpath, newpath), Access)

FUNC(int, rmdir, arg(const char *pathname), arg(pathname), -1, arg(pathname), Access)

FUNC(int, __xstat, arg(const char *pathname, struct stat *statbuf), arg(pathname, statbuf), -1, arg(pathname), Access)
FUNC(int, __xstat64, arg(const char *pathname, struct stat *statbuf), arg(pathname, statbuf), -1, arg(pathname), Access)

FUNC(int, symlink, arg(const char *target, const char *linkpath), arg(target, linkpath), -1, arg(target, linkpath), Access)

FUNC(int, unlink, arg(const char *pathname), arg(pathname), -1, arg(pathname), Access)

FUNC(int, execl, arg(const char *path, const char *arg, ...), arg(path, arg), -1, arg(nullptr), Exec)

FUNC(int, execle, arg(const char *path, const char *arg, ...), arg(path, arg), -1, arg(nullptr), Exec)

FUNC(int, execlp, arg(const char *file, const char *arg, ...), arg(file, arg), -1, arg(nullptr), Exec)

FUNC(int, execv, arg(const char *path, char *const argv[]), arg(path, argv), -1, arg(nullptr), Exec)

FUNC(int, execve, arg(const char *pathname, char *const argv[], char *const envp[]), arg(pathname, argv, envp), -1, arg(nullptr), Exec)

FUNC(int, execvp, arg(const char *file, char *const argv[]), arg(file, argv), -1, arg(nullptr), Exec)

FUNC(int, system, arg(const char *command), arg(command), -1, arg(nullptr), Exec)
*/