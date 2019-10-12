//
// Created by Екатерина on 2019-10-03.
//


#include "minishell.h"

void reset_input_tmode(void)
{
	tcsetattr(0, TCSANOW, &g_saved_attributes);
}

void exit_clean(void)
{
//	clean_env(g_shell->env);

//	free(g_shell->history->path);
	clean_env(g_shell->history->cmnds);
	if (g_shell->input)
	{
//		free(g_shell->input->line);
//		free(g_shell->input->clipboard);
//		free(g_shell->input);
	}
	exit(EXIT_SUCCESS);
}

void init_term(void)
{
	char *term_type;
	static char term_buffer[MAXLINE];
	int res;

	if ((term_type = ft_getenv("TERM")))
	{
		if (!(res = tgetent(term_buffer, term_type)))
		{
			perror_cmnd(SHELLNAME, NULL, TTYNOTDFND);
			exit_clean();
		}
		if (res < 0)
		{
			perror_cmnd(SHELLNAME, NULL, NOTERMCAP);
			exit_clean();
		}
	}
	else
	{
		perror_cmnd(SHELLNAME, NULL, SPECTTY);
		exit_clean();
	}
}

void set_input_tmode(void)
{
	struct termios tattr;
	if (!isatty(STDIN_FILENO))
	{
		perror_cmnd(SHELLNAME, NULL, NOTTERM);
		exit_clean();
	}
	init_term(); //finding a term description
	if (tcgetattr(STDIN_FILENO, &g_saved_attributes) == -1)
	{
		perror_cmnd(SHELLNAME, NULL, TCGETATTR);
		exit_clean();
	}
	ft_memcpy(&tattr, &g_saved_attributes, sizeof(tattr));
	// включаем неканонический режим без эха //отключаем сигналы INTR, QUIT, [D]SUSP
	tattr.c_lflag &= ~(ICANON|ECHO); //ISIG
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &tattr);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr) == -1)
	{
		perror_cmnd(SHELLNAME, NULL, TCSETATTR);
		exit_clean();
	}
}

//char *get_histpath(void)
//{
//	char *path;
//
//	if ((path = getenv_cmnd("PWD")))
//		return (ft_strjoin(path, HISTFILE));
//	return (NULL);
//}


//O_CREAT если файл не существует, то он будет создан
//S_IRUSR (S_IREAD) (00400 пользователь имеет права на чтение файла);
//S_IWUSR (S_IWRITE) (00200 пользователь имеет права на запись информации в файл);
t_history *init_history()
{
	int fd;
	char *histsize;
	char *histfilesize;
	int index;
//	char **prevcmnds;
	t_history *history;


	history = ft_memalloc(sizeof(t_history));

	char *path;
	if ((path = ft_getenv("PWD")))
		history->path = ft_strjoin(path, HISTFILE);
	if ((fd = open(history->path, (O_RDWR|O_CREAT), (S_IREAD|S_IWRITE))) == -1)
		perror_cmnd(SHELLNAME, NULL, OPENERR);
	if ((histsize = ft_getenv("HISTSIZE")))
		history->size = ft_atoi(histsize);
	else
		history->size = HISTSIZE;
	if ((histfilesize = ft_getenv("HISTFILESIZE")))
		history->size = ft_atoi(histfilesize);
	else
		history->size = HISTFILESIZE;
	if (!(history->cmnds = (char**)malloc(sizeof(char*) * (history->size + 1))))
		perror_cmnd(SHELLNAME, NULL, MLKERR);
	if (history->cmnds)
	{
		index = 0;
		while (index < history->size && get_next_line(fd, &(history->cmnds[index])) > 0)
			index++;
		history->cmnds[index] = NULL;
	}
	if (close(fd) == -1)
		perror_cmnd(SHELLNAME, NULL, CLOSEERR);
	return (history);
}