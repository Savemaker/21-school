#include <fcntl.h>
#include <stdio.h>
#include "21sh.h"

int main(void)
{
	int fd;
	int fd1;
	int fd2;
	int orig;

	
	fd = open("1", O_RDWR | O_CREAT, 0644);
	fd1 = open("2", O_RDWR | O_CREAT, 0644);
	fd2 = open("3", O_RDWR | O_CREAT, 0644);
	orig = dup(1);
	dup2(fd, orig);
	// dup2(fd1, 1);
	// dup2(fd2, 1);
	ft_putstr("yay");
	return (0);
}