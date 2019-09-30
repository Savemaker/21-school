#include <fcntl.h>
#include <stdio.h>
#include "21sh.h"

int main(void)
{
	int fd;
	int fd1;
	int fd2;
	int orig;

	orig = dup(1);
	fd = open("file", O_RDONLY);
	return (0);
}