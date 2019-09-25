#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
    int fd;
    char *ls[] = {"cat", NULL};

    fd = open("1", O_RDONLY);
    dup2(fd, 0);
    execvp("cat", ls);
    return (0);
}