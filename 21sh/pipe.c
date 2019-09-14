#include "21sh.h"

typedef struct		my_pipe{
	char			**cmd;
	struct	my_pipe	*next;
	int				fd_in;
	int				fd_out;
}my_pipe;


void	execute_pipe(my_pipe *new)
{
	int fd[2];

	while (new)
	{
		pipe(fd);
		if (fork() == 0)
		{
			dup2(new->fd_in, 0);
			if (new->next)
				dup2(fd[1], 1);
			close(fd[0]);
			execvp(new->cmd[0], new->cmd);
		}
		else
			close(fd[1]);
			if (new->next)
				new->next->fd_in = fd[0];
		new = new->next;
	}
}