/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:22:33 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/10 16:31:58 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# define TRUE 1
# define FALSE 0

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
# include "../libft/libft.h"

typedef struct s_node
{
    char			**cmd;
    char			*path;
    int				in_fd;
	int				out_fd;
    struct s_node	*next; 
}t_node;

typedef struct s_util
{
    int start;
    int end;
    int idx;
    int i;
    int j;
    int flag;
}t_util;

typedef struct s_env
{
	char	*line;
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

/* builtin */
void	ft_cat(t_node *node);
void	ft_cd(t_node *node);
void	ft_echo(t_node *node);
void	ft_env(t_env *env_head);
void	ft_exit(t_node *node);
void ft_export(t_env *env_head, t_node *node);
void	ft_pwd(t_node *node);
void	ft_unset(t_node *node);

/* env */
t_env	*create_env_node(char *env_line);
void	add_env_node_backward(t_env **head, t_env *new_node);
int		count_env_node(t_env *head);
t_env	*get_env(t_env *head, char **envp);

/* node */
t_node	*create_cmd_node(void);
void	add_cmd_node_backward(t_node **head, t_node *new_node);
int		count_cmd_node(t_node *head);

/* exec */
int		is_builtin(t_node *node);
int		exec_builtin(t_env *env_head, t_node *node);

int		run_cmd(t_env *env_head, t_node *node);

void	fork_process(t_env *env_head, t_node *node_head, int node_cnt);

char	**env_to_char(t_env *env_head);

int		is_redirection(t_node *node);


//minishell.c
void	minishell(char *str);
void	sig_handler(int signal);
//parsing.c
char	***parsing(char *av);
char	**split_flag(char *av, int len, char flag);
char	*save_in(char *av, t_util *util);
int		find_other(char *av, int idx);
//parsing_in_pipe.c
void	is_outfd(char **str, int *i, t_node *node);
void	is_infd(char **str, int *i, t_node *node);
char	**find_fd(char **str, t_node *node);
void	parsing_in_pipe(char *av, t_node *node);
char	*add_space(char *av);
//parsing_util.c
void	save_in_node(t_node *node, char **cmd);
int		find_flag(char *av, char flag);
int		find_next_quote(char *av, int idx, char flag);
void	util_init(t_util *util);
t_node	*make_node(t_node *node);
//parsing_free.c
void	free_str(char **str);
void	free_str_three(char ***str);
void	free_node(t_node *head);
//paring_fd.c
void	new_file(char **str, int *i, t_node *node);
void	append_file(char **str, int *i, t_node *node);
void	check_infile(char **str, int *i, t_node *node);
void	heredoc_infile(char **str, int *i, t_node *node);
void	heredoc_process(char **str, int *i, t_node *node);

char    *del_quote(char *av);
char	**split_space(char *av, int len);
char	**check_cmd(char **av);
#endif