#include "includes/minishell.h"

int main(void)
{
    char *a= "../../.q..";
    char *c;

    char *b = ft_strdup(a);
    c = ft_strtrim(b,"./");
    if (!c[0])
        printf("asdasd");
    else
        printf("%s\n",c);
    return (1);
}