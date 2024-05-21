#include "../../includes/minishell.h"

void	save_in_node(t_node *node, char **cmd, t_env *env)
{
	int	i;

	i = count_str(cmd);
	node->cmd = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (cmd[++i])
		node->cmd[i] = ft_strdup(cmd[i]);
	node->cmd[i] = NULL;
	find_path(cmd[0], env, node);
}



t_node	*create_node(int p_e)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->cmd = NULL;
	node->path = NULL;
	node->in_fd = 0;
	node->out_fd = 1;
	node->prev_errnum = p_e;
	return (node);
}

void	append_node(t_node **head, t_node *new_node)
{
	t_node	*cur;

	cur = *head;
	if (!cur)
		(*head) = new_node;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new_node;
	}
}
