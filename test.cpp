#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/stat.h>
#include <getopt.h>
#include <string>
#include <string.h>

#define MAXARGS 31

using namespace std;

void argsFree(char **args){
    for(int i=0;args[i]!= nullptr;++i)
        free(args[i]);
}

__attribute__((constructor)) void init(){
    unsetenv("LD_PRELOAD");
    setenv("LD_PRELOAD", "./sandbox.so", true);
}

int main(int argc, const char **argv) {
    /*
     * We have to implement dynamic loading our .so library
     */    
    chmod("file", 0644);
    system("");
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-p") == 0){
            setenv("LD_PRELOAD", argv[i+1], true);
            ++i;
        } else if (strcmp(argv[i], "-d") == 0){
            setenv("PWD", argv[i+1], true);
            ++i;
        } else if (strcmp(argv[i], "--") == 0){
            char *args[MAXARGS];
            int length = 0;
            for(; i<argc-1;++length, ++i)
                args[length] = strdup(argv[i+1]);
            args[length] = nullptr;
            if (execvp(args[0], args) < 0)
                fprintf(stderr, "Unknown command: [%s].\n", args[0] );
            argsFree(args);
        } else{
            printf("usage: ./sandbox [-p sopath] [-d basedir] [--] cmd [cmd args ...]\n"
                   "        -p: set the path to sandbox.so, default = ./sandbox.so\n"
                   "        -d: the base directory that is allowed to access, default = .\n"
                   "        --: separate the arguments for sandbox and for the executed command\n");
        }
    }
    return 0;
}

