/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:22:33 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/12 03:56:57 by dongwook         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
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
	int	start;
	int	end;
	int	idx;
	int	i;
	int	j;
	int	flag;
	int	cnt;
}t_util;

typedef struct s_env
{
	char	**arr;
	char	**arr_export;
}	t_env;

/* ↓↓↓↓↓ ======== EXEC ======== ↓↓↓↓↓ */

/* minishell.c */
void	minishell(char *str, char **evnp);
void	sig_handler(int signal);

/* parsing.c */
char	***parsing(char *av);
char	**split_flag(char *av, int len, char flag);
char	*save_in(char *av, t_util *util);
int		find_other(char *av, int idx);

/* parsing_in_pipe.c */
void	is_outfd(char **str, int *i, t_node *node);
void	is_infd(char **str, int *i, t_node *node);
char	**find_fd(char **str, t_node *node);
void	parsing_in_pipe(char *av, t_node *node);
char	*add_space(char *av);

/* parsing_util.c */
void	save_in_node(t_node *node, char **cmd);
int		find_flag(char *av, char flag);
int		find_next_quote(char *av, int idx, char flag);
void	util_init(t_util *util);
// t_node	*make_node(t_node *node); // dongwook
t_node	*create_node(void);
void	append_node(t_node **head, t_node *new_node);

/* parsing_free.c */
void	free_str(char **str);
void	free_str_three(char ***str);
void	free_node(t_node *head);

/* paring_fd.c */
void	new_file(char **str, int *i, t_node *node);
void	append_file(char **str, int *i, t_node *node);
void	check_infile(char **str, int *i, t_node *node);
void	heredoc_infile(char **str, int *i, t_node *node);
void	heredoc_process(char **str, int *i, t_node *node);
char    *del_quote(char *av);
char	**split_space(char *av, int len);
char	**check_cmd(char **av);

/* ↓↓↓↓↓ ======== EXEC ======== ↓↓↓↓↓ */

/* builtin */
void	ft_cat(t_node *node);
void	ft_cd(t_node *node);
void	ft_echo(t_node *node);
void	ft_env(t_env *env);
void	ft_exit(t_node *node);
void	ft_export(t_env *env, t_node *node);
void	ft_pwd(t_node *node);
void	ft_unset(t_node *node);

/* env */
int		env_init(t_env *env, char **envp);

/* exec */
int		is_builtin(t_node *node);
int		exec_builtin(t_env *env, t_node *node);
int		run_cmd(t_env *env, t_node *node);
void	fork_process(t_env *env, t_node *node, int node_cnt);
void	wait_process(int cnt);
void	close_pipe(int *fd);
void	redirect_io(int in_fd, int out_fd);
int		count_node(t_node *node);

/* utils */
void	ft_free(void **target);
void	ft_free_2d(char **str);
void	print_node_details(t_node *node);
void	print_linked_list(t_node *head);
#endif
