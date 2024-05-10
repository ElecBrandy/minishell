#include "../../includes/minishell.h"

char	**check_cmd(char **av)
{
	int		i;
	char	**str;

	i = 0;
	while (av[i])
		i++;
	str = malloc(sizeof(char *) * (i + 1));
	str[i] = NULL;
	i = -1;
	while (av[++i])
		str[i] = del_quote(av[i]);
	free_str(av);
	return (str);
}

char	**split_space(char *av, int len)
{
	char	**str;
	t_util	util;

	util_init(&util);
	str = (char **)malloc(sizeof(char *) * (len + 2));
	if (!str)
		exit(1);
	while (av[++util.idx])
	{
		if (av[util.idx] == ' ')
		{
			if (av[util.idx + 1] != ' ')
				str[++util.i] = save_in(av, &util);
		}
		else
			util.idx = find_other(av, util.idx);
	}
	if (util.flag == 0)
		str[++util.i] = save_in(av, &util);
	else
		str[++util.i] = save_in(av, &util);
	str[++util.i] = NULL;
	return (str);
}

char    *del_quote(char *av)
{
	t_util	u;
	int		cut;
	char	*str;

	cut = 0;
	util_init(&u);
	while (av[++u.i])
	{
		// if (av[i] == 34) // "" $
		// {
		// 	i = find_next_quote(av, i, 34);
		// 	cut += 2;
		// }
		if (av[u.i] == 39)
		{
			u.i = find_next_quote(av, u.i, 39);
			cut += 2;
		}
	}
	str = malloc(sizeof(char) * (u.i - cut + 1));
	u.i = -1;
	while (av[++u.i])
	{
		if (av[u.i] == 39)
		{
			if (u.flag == 0)
			{
				u.flag = 1;
			}
			else
			{
				u.flag = 0;
			}
		}
		else
			str[++u.idx] = av[u.i];
	}
	str[++u.idx] = '\0';
	return (str);
}
