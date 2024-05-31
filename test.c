#include "includes/minishell.h"

void    readline2()
{
    pid_t   pid;
    char    *str;
    int     status;
    pid = fork();

    if (pid == 0)
    {
        while (1)
        {
            signal(SIGQUIT, SIG_IGN);
            str = readline("22 ");
            if (!str)
            {
                printf("exit\n");
                exit (0);
            }
            else if (*str == '\0')
                free(str);
            else
            {
                add_history(str);
                free(str);
            }
        }
    }
    wait(&status);
}

int main(void)
{
    char *av;

    while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		av = readline("mimishell$ ");
		if (!av)
		{
			printf("exit\n");
			exit (0);
		}
		else if (*av == '\0')
			free(av);
		else
		{
			add_history(av);
            readline2();
			free(av);
		}
	}
    exit (0);
}