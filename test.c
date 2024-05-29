#include "includes/minishell.h"

int	ft_find_word(char *str, const char *word)
{
	int	i;
	int	j;
	int	start;
	i = -1;
	while (str[++i])
	{
		start = 0;
		if (str[i] == word[start])
		{
			j = i;
			printf("start\n");
			while (str[j])
			{
				printf("ing~\n");
				if (str[j] != word[start])
					break ;
				j++;
				start++;
				if (word[start] == 0)
					return (1);
			}
		}
	}
	return (0);
}

int	main(void)
{
	const char	*cmds[18];

	cmds[0] = "wc";
	cmds[1] = "cmp";
	cmds[2] = "awk";
	cmds[3] = "split";
	cmds[4] = "cat";
	cmds[5] = "cut";
	cmds[6] = "sed";
	cmds[7] = "tr";
	cmds[8] = "diff";
	cmds[9] = "diff3";
	cmds[10] = "grep";
	cmds[11] = "egrep";
	cmds[12] = "fgrep";
	cmds[13] = "head";
	cmds[14] = "tail";
	cmds[15] = "rev";
	cmds[16] = "sort";
	cmds[17] = NULL;
	// int i=-1;
	// while (cmds[++i])
	// {
	// 	printf ("%d\n", i);
		if (ft_find_word("cat", cmds[4]))
			printf("ok\n");
//	}
	return (1);
}
