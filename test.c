#include "includes/minishell.h"

int main(int ac, char **av, char **env)
{
    char    **str;
    char    **str2;
    char    *word;
    char    *a = "VSCODE_GIT_ASKPASS_MAIN";
    int     i=-1;
    if (ac == 0 || !av)
        exit(1);
    while (env[++i])
    {
        if (ft_strncmp(env[i], a, ft_strlen(a)) == 0)
            word = ft_strdup(env[i]);
    }
    str = ft_split(word, '=');
    printf("%s\n", str[1]);
    str2 = ft_split(str[1], ' ');
    i = -1;
    while (str2[++i])
    {
        printf("%s\n", str2[i]);
    }
    exit (0);
}