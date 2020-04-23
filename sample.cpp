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

#define	FILE_A	"file"
#define	FILE_B	"/tmp/bbb"
#define	FILE_NULL	"/dev/null"
int main(int argc, const char **argv) {
	struct stat st;
	char *args[] = { FILE_A, NULL };
	char buf[128];
	chdir(".");
	chmod(FILE_A, 0644);
	chown(FILE_A, 0, 0);
	creat(FILE_A, O_RDONLY);
	fopen(FILE_A, "rt");
	link(FILE_A, FILE_B);
	mkdir(FILE_A, 0755);
	open(FILE_A, O_RDONLY);
	openat(AT_FDCWD, FILE_A, 0755);
	opendir(FILE_A);
	readlink(FILE_NULL, buf, sizeof(buf));
	remove(FILE_A);
	rename(FILE_A, FILE_B);
	rmdir(FILE_A);
	stat(FILE_NULL, &st);
	symlink(FILE_A, FILE_B);
	unlink(FILE_A);
	execl(FILE_A, FILE_A, NULL);
	execle(FILE_A, FILE_A, NULL, NULL);
	execlp(FILE_A, FILE_A, NULL);
	execv(FILE_A, args);
	execvp(FILE_A, args);
	execve(FILE_A, args, NULL);
	system("echo -n");
    return -1;
}
