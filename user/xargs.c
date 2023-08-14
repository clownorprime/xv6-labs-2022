#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXLINE 100

int
main(int argc, char *argv[])
{
	char* arg[MAXARG];
	int row, col;
	char c;
	char buf[MAXLINE];

	if (argc < 2) {
		fprintf(2, "bad input");
		exit(1);
	}

	for (int i = 0; i < argc - 1; i++) {
		arg[i] = argv[i+1];
	}
	row = argc - 1;
	col = 0;
	while(read(0, &c, 1) != 0) {
		if (c == '\n') {
			buf[col] = '\0';
			arg[row] = buf;
			row++;
			col = 0;
		} else {
			buf[col++] = c;
		}
	}
	arg[row] = 0;
	exec(argv[1], arg);
	exit(1);
}

