#include "../../includes/minishell.h"

void	print_error(void)
{
	if (g_errnum == 0)
		g_errnum = 12;
	if (g_errnum == -1)
	{
		printf("minishell: syntax error: unexpected end of file\n");
		g_errnum = 258;
		errno = 258;
	}
	else if (g_errnum == 1)
		return ;
	else if (g_errnum == 127)
		return ;
	else if (g_errnum == 258)
	{
		printf("minishell: syntax error: unexpected token\n");
		errno = 258;
	}
	else
	{
		errno = g_errnum;
		perror("minishell");
	}
}