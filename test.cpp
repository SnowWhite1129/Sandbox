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

using namespace std;
#define  MAXARGS     31

void argsFree(char **args){
    for(int i=0;args[i]!= nullptr;++i)
        free(args[i]);
}
int main(int argc, const char **argv) {
    /*
     * We have to implement dynamic loading our .so library
     */
    system(argv[1]);
//    bool command = false;
//    for (int i = 0; i < argc; ++i) {
//        if (strcmp(argv[i], "-p") == 0){
//
//            ++i;
//        } else if (strcmp(argv[i], "-d") == 0){
//
//            ++i;
//        } else if (strcmp(argv[i], "--") == 0){
//            for(int j=i; j<argc;j++)
//                args[j] = strdup(argv[i]);
//            args[argc] = nullptr;
//            if (execvp(args[0], args) < 0)
//                fprintf(stderr, "Unknown command: [%s].\n", args[0] );
//            argsFree(args);
//
//            command = true;
//        } else if (!command) {
//
//        } else{
//
//        }
//    }
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
    return -1;
}

