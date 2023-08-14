#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void aux(int fd[2]);

int 
main(int argc, char* argv[]) 
{
	int fd[2];

	if (argc != 1) {
		printf("bad input. Usage: %s\n", argv[0]);
		exit(1);
	}
	pipe(fd);
	for (int i = 2; i <= 35; i++) {
		write(fd[1], &i, sizeof(int));
	}
	aux(fd);
	exit(0);
}

void aux(int fd[2]) 
{
	int pid, ret, prime, num;
	int fd_aux[2];
	close(fd[1]);
	if ((ret = read(fd[0], &prime, sizeof(int))) < 0) {
		printf("read error\n");
		exit(1);
	}
	if (ret == 0) {			// end of the pipe
		return;
	}
	printf("prime %d\n", prime);

	pipe(fd_aux);
	pid = fork();
	if (pid < 0) {
		printf("fork error\n");
		exit(1);
	}
	if (pid > 0) {
		close(fd_aux[0]);
		while(read(fd[0], &num, sizeof(int)) > 0) {
			if (num % prime != 0) {
				write(fd_aux[1], &num, sizeof(int));
			}
		}
		close(fd[0]);
		close(fd_aux[1]);
		wait(0);
	} 
	if (pid == 0) {
		aux(fd_aux);
	}
	exit(0);
}
