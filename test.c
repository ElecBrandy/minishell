#include "includes/minishell.h"

int	main(void)
{

	if (access("ls", X_OK) == 0)
		printf("ok\n");
	return (1);
}
