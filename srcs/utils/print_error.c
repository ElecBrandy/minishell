#include "../../includes/minishell.h"

void	print_error(void)
{
	g_errnum = 12;
	errno = g_errnum;
	perror("minishell");
}