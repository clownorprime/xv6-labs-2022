#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int 
main(int argc, char* argv[]) 
{
	int pid;
	int fd1[2], fd2[2];

	pipe(fd1);
	pipe(fd2);
	
	pid = fork();
	if(pid == 0) {
		char c[5];
		close(fd1[1]);
		read(fd1[0], &c, 4);
		c[4] = '\0';
		printf("%d: received %s\n", getpid(), c);
		close(fd1[0]);
		close(fd2[0]);
		write(fd2[1], "pong", 4);
		close(fd2[1]);
		exit(0);
	}
	// parent process
	char c[5];
	close(fd1[0]);
	write(fd1[1], "ping", 4);
	close(fd1[1]);
	close(fd2[1]);
	read(fd2[0], &c, 4);
	close(fd2[0]);
	c[4] = '\0';
	printf("%d: received %s\n", getpid(), c);
	close(fd2[0]);
	exit(0);
}
