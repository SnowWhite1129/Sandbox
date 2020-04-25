#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <getopt.h>
#include <string.h>

#define MAXARGS 31

__attribute__((constructor)) void init(){
    unsetenv("LD_PRELOAD");
    setenv("LD_PRELOAD", "./sandbox.so", true);
    setenv("BASEDIR", ".", true);
}

int main(int argc, const char **argv) {
    char *args[MAXARGS];
    int length = 0;
    bool start = false;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]){
                case 'p':
                    setenv("LD_PRELOAD", argv[i+1], true);
                    ++i;
                    break;
                case 'd':
                    setenv("BASEDIR", argv[i+1], true);
                    ++i;
                    break;
                case '-':
                    start = true;
                    break;
                default:
                    if (start){
                        args[length] = strdup(argv[i]);
                        ++length;
                    } else{
                        printf("usage: ./sandbox [-p sopath] [-d basedir] [--] cmd [cmd args ...]\n"
                               "        -p: set the path to sandbox.so, default = ./sandbox.so\n"
                               "        -d: the base directory that is allowed to access, default = .\n"
                               "        --: separate the arguments for sandbox and for the executed command\n");
                        return 0;
                    }
                    break;
            }
        } else {
            args[length] = strdup(argv[i]);
            ++length;
        }
    }
    args[length] = nullptr;
    if (execvp(args[0], args) < 0)
        fprintf(stderr, "Unknown command: [%s].\n", args[0]);
    return 0;
}

