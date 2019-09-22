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


void     execute_tree(tree *ast)    // 0 = def exe             1 = output to pipe      2 = take pipe
{
	int tmp;
	int fd[2];
	pid_t ls;
	pid_t cat;
	pid_t grep;
	pipe(fd);
	ls = fork();
	if (ls == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		create_argv(ast->left->left);
		execvp(ast->left->left->argv[0], ast->left->left->argv);
	}
	else
	{
		waitpid(ls, NULL, 0);
		close(fd[1]);
		tmp = fd[0];
		pipe(fd);
		cat = fork();
		if (cat == 0)
		{
			dup2(tmp, 0);
			close(fd[0]);
			dup2(fd[1], 1);
			create_argv(ast->left->right);
			execvp(ast->left->right->argv[0], ast->left->right->argv);
		}
		else
		{
			waitpid(cat, NULL, 0);
			close(fd[1]);
			close(tmp);
			grep = fork();
			if (grep == 0)
			{
				dup2(fd[0], 0);
				close(fd[1]);
				create_argv(ast->right);
				execvp(ast->right->argv[0], ast->right->argv);
			}
			else
			{
				waitpid(grep, NULL, 0);
				close(fd[0]);
			}
		}
			
	}
}