#include "../../includes/minishell.h"

void	get_path(char **path, t_node *node, char *cmd)
{
	int	i;

	i = -1;
    if (is_builtin(node) == 0)
    {
        while (path[++i])
        {
            node->path = ft_strjoin(path[i], "/");
            node->path = ft_strjoin_free(node->path, cmd);
            if (access(node->path, X_OK) == 0)
                return ;
            else
                free(node->path);
        }
        if (!path[i])
            exit (2);
    }
    else
    {
        node->path = ft_strdup(cmd);
    }
}

void	find_path(char *cmd, t_env *env, t_node *node)
{
	char	*env_path;
	char	**path;
	int		i;
	t_env	*e;

	e = env;
	while (e->cmd)
	{
		if (ft_strncmp(e->key, "PATH", 4) == 0)
			break ;
		e = e->next;
	}
	env_path = ft_strdup(e->value);
	path = ft_split(env_path, ':');
	free(env_path);
	if (access(cmd, X_OK) == 0)
	{
		node->path = ft_strdup(cmd);
		return ;
	}
	get_path(path, node, cmd);
	free_str(path);
}
