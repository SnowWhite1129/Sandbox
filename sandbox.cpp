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

#define  MAXARGS     31
struct DIR;
char *args[MAXARGS];
string basedir;
bool permission(const char *path){
    return strcmp(path, basedir.c_str())==0;
}
DIR* opendir(const char *name){
    if(!permission(name)){
        printf("[sandbox] opendir: access to / is not allowed");
    }
}
void argsFree(char **args){
    for(int i=0;args[i]!= nullptr;++i)
        free(args[i]);
}
int main(int argc, const char **argv){
//    char c;
//    while((c=getopt(argc, argv, "p:d:-:")) != -1)
//    {
//        switch(c)
//        {
//            case 'p':
//                break;
//            case 'd':
//                break;
//            case '-':
//
//                break;
//            case '?':
//                system("");
//                break;
//            default:
//                printf("usage: ./sandbox [-p sopath] [-d basedir] [--] cmd [cmd args ...]\n"
//                       "        -p: set the path to sandbox.so, default = ./sandbox.so\n"
//                       "        -d: the base directory that is allowed to access, default = .\n"
//                       "        --: separate the arguments for sandbox and for the executed command\n");
//                break;
//        }
//    }
    bool command = false;
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-p") == 0){

        } else if (strcmp(argv[i], "-d") == 0){

        } else if (strcmp(argv[i], "--") == 0){
            for(int j=i; j<argc;j++)
                args[j] = strdup(argv[i]);
            args[argc] = nullptr;
            if (execvp(args[0], args) < 0)
                fprintf(stderr, "Unknown command: [%s].\n", args[0] );
            argsFree(args);

            command = true;
        } else if (!command) {

        } else{

        }
    }
}