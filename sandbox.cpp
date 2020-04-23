#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <cstdio>

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
    auto lib_##fnptr = reinterpret_cast<type (*)(args)>(dlsym(handle, #func_name));/* function pointer */ \
    fprintf(stderr, "Injected\n");          \
                                            \
    if(lib_##fnptr){                        \
        if (!permission()){                 \
            errmsg(#func_name);             \
        }                              \
        type ret = lib_##fnptr(args2);  \
        dlclose(handle);                \
        return ret;                                   \
    }                                       \
}

FUNC(int, chdir, arg(const char *path), arg(path))

FUNC(int, chmod, arg(char* path, mode_t mode), arg(path, mode))

FUNC(int, chown, arg(const char *pathname, uid_t owner, gid_t group), arg(pathname, owner, group))

FUNC(int, creat, arg(const char *pathname, mode_t mode), arg(pathname, mode))
FUNC(int, creat64, arg(const char *pathname, mode_t mode), arg(pathname, mode))

FUNC(FILE*, fopen, arg(const char *pathname, const char *mode), arg(pathname, mode))
FUNC(FILE*, fopen64, arg(const char *pathname, const char *mode), arg(pathname, mode))

FUNC(int, link, arg(const char *oldpath, const char *newpath), arg(oldpath, newpath))

FUNC(int, mkdir, arg(const char *pathname, mode_t mode), arg(pathname, mode))

FUNC(int, open, arg(const char *pathname, int flags), arg(pathname, flags))
FUNC(int, open64, arg(const char *pathname, int flags), arg(pathname, flags))
FUNC(int, open, arg(const char *pathname, int flags, mode_t mode), arg(pathname, flags, mode))
FUNC(int, open64, arg(const char *pathname, int flags, mode_t mode), arg(pathname, flags, mode))

FUNC(int, openat, arg(int dirfd, const char *pathname, int flags), arg(dirfd, pathname, flags))
FUNC(int, openat64, arg(int dirfd, const char *pathname, int flags), arg(dirfd, pathname, flags))
FUNC(int, openat, arg(int dirfd, const char *pathname, int flags, mode_t mode), arg(dirfd, pathname, flags, mode))
FUNC(int, openat64, arg(int dirfd, const char *pathname, int flags, mode_t mode), arg(dirfd, pathname, flags, mode))

FUNC(struct DIR*, opendir, arg(const char *name), arg(name))

FUNC(ssize_t , readlink, arg(const char *pathname, char *buf, size_t bufsiz), arg(pathname, buf, bufsiz))

FUNC(int, remove, arg(const char *pathname), arg(pathname))

FUNC(int, rename, arg(const char *oldpath, const char *newpath), arg(oldpath, newpath))

FUNC(int, rmdir, arg(const char *pathname), arg(pathname))

FUNC(int, __xstat, arg(const char *pathname, struct stat *statbuf), arg(pathname, statbuf))
FUNC(int, __xstat64, arg(const char *pathname, struct stat *statbuf), arg(pathname, statbuf))

FUNC(int, symlink, arg(const char *target, const char *linkpath), arg(target, linkpath))

FUNC(int, unlink, arg(const char *pathname), arg(pathname))

FUNC(int, execl, arg(const char *path, const char *arg, ...), arg(path, arg))

FUNC(int, execle, arg(const char *path, const char *arg, ...), arg(path, arg))

FUNC(int, execlp, arg(const char *file, const char *arg, ...), arg(file, arg))

FUNC(int, execv, arg(const char *path, char *const argv[]), arg(path, argv))

FUNC(int, execve, arg(const char *pathname, char *const argv[], char *const envp[]), arg(pathname, argv, envp))

FUNC(int, execvp, arg(const char *file, char *const argv[]), arg(file, argv))

FUNC(int, system, arg(const char *command), arg(command))
