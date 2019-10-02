#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	char *cat[] = {"cat", NULL};
	int in;
	int out;
	int p;

	out = open("2", O_CREAT | O_RDWR, 0644);
	in = 0;
	p = fork();
	if (p == 0)
	{
		dup2(in, 0);
		dup2(out, 1);
		execvp(cat[0], cat);
	}
	else
	{
		waitpid(p, NULL, 0);
	}
	return (0);
}