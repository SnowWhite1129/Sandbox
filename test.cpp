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

#define	FILE_A	"/tmp/aaa"
#define	FILE_B	"/tmp/bbb"
#define	FILE_NULL	"/dev/null"
#define  MAXARGS     31
char *args[MAXARGS];
string basedir;

void argsFree(char **args){
    for(int i=0;args[i]!= nullptr;++i)
        free(args[i]);
}
int main(int argc, const char **argv) {
//	struct stat st;
//	char *args[] = { FILE_A, NULL };
//	char buf[128];
//	chdir(".");
	chmod(FILE_A, 0644);
//	chown(FILE_A, 0, 0);
//	creat(FILE_A, O_RDONLY);
//	fopen(FILE_A, "rt");
//	link(FILE_A, FILE_B);
//	mkdir(FILE_A, 0755);
//	open(FILE_A, O_RDONLY);
//	openat(AT_FDCWD, FILE_A, 0755);
//	opendir(FILE_A);
//	readlink(FILE_NULL, buf, sizeof(buf));
//	remove(FILE_A);
//	rename(FILE_A, FILE_B);
//	rmdir(FILE_A);
//	stat(FILE_NULL, &st);
//	symlink(FILE_A, FILE_B);
//	unlink(FILE_A);
//	execl(FILE_A, FILE_A, NULL);
//	execle(FILE_A, FILE_A, NULL, NULL);
//	execlp(FILE_A, FILE_A, NULL);
//	execv(FILE_A, args);
//	execvp(FILE_A, args);
//	execve(FILE_A, args, NULL);
//	system("echo -n");
//    bool command = false;
//    for (int i = 0; i < argc; ++i) {
//        if (strcmp(argv[i], "-p") == 0){
//
//        } else if (strcmp(argv[i], "-d") == 0){
//
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

