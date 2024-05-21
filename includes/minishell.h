/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:22:33 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/18 12:49:09 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0

# define STDIN 0
# define STDOUT 1

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
# include <termios.h>
# include "../libft/libft.h"

typedef struct s_node
{
	char			**cmd;
	char			*path;
	int				in_fd;
	int				out_fd;
	int				prev_errnum;
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
	char	*cmd;
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

int		g_errnum;
/* ↓↓↓↓↓ ======== PARSER ======== ↓↓↓↓↓ */
/* minishell.c */
void	minishell(char *av, t_env *head_env);
void	sig_handler(int signal);
void	readline_minishell(t_env *env);
int		parsing_minishell(t_node **head, char **str, t_env *env, int p_e);

/* parsing_dollar_find.c */
char	*get_word(char *av, int *idx);
int		find_env(char *av, int *idx, t_env *env);
int		find_dollar(char *av, t_env *env, int p_e);
int		is_print(char s);
void	jump_next_word(char *av, t_util *u);

/* parsing_dollar_put.c */
void	put_str(char *str, char *av, int *a_idx, int *s_idx);
void	put_word(char *av, char *word, int *idx);
void	put_env(char *str, char *av, t_env *env, t_util *u);
void	put_change_dollar(char *av, char *str, t_env *env, t_util *u);
void	put_dollar(char *av, char *str, t_util *u);

/* parsing_delquote.c */
char	*del_quote(char *av);
char	**split_space(char *av, int len);
char	**check_cmd(char **av);
int		find_cut(char *av);
void	del_q(char *av, char *str, t_util *u);

/* parsing_dollar.c */
char	*check_dollar(char *av, t_env *env, int p_e);
char	*change_dollar(char *av, t_env *env, int env_len, int p_e);

/* parsing_error.c*/
int		get_numlen(int num);
void	put_errno(char *str, char *av, int p_e, t_util *u);

/* parsing_free.c */
void	free_str(char **str);
void	free_str_three(char ***str);
void	free_node(t_node *head);
int		count_str(char **str);

/* parsing_heredoc_dollar.c*/
void	putin_doublequote(char *av, char *str, t_env *env, t_util *u);
char	*heredoc_change_dollar(char *av, t_env *env, int env_len, int p_e);
int		heredoc_find_dollar(char *av, t_env *env, int p_e);
void	in_doublequote(char *av, int p_e, t_env *env, t_util *u);

/* parsing_heredoc.c */
void	heredoc_infile(char **str, int *i, t_node *node, t_env *env);
void	heredoc_process(char **str, int *i, t_node *node, t_env *env);
char	*heredoc_check_dollar(char *av, t_env *env, t_node *node);
int		heredoc_readline(char *av, char *limiter, t_node *node, t_env *env);

/* parsing_in_pipe.c */
int		parsing_in_pipe(char *av, t_node *node, t_env *env, int p_e);
char	*add_space(char *av);

/* paring_infd.c */
void	check_infile(char **str, int *i, t_node *node);
void	only_open(char **str, int *i);
void	is_infd(char **str, int *i, t_node *node, t_env *env);

/* parsing_node.c */
void	save_in_node(t_node *node, char **cmd, t_env *env);
t_node	*create_node(int p_e);
void	append_node(t_node **head, t_node *new_node);

/* parsing_outfd.c */
void	new_file(char **str, int *i, t_node *node);
void	append_file(char **str, int *i, t_node *node);
void	is_outfd(char **str, int *i, t_node *node);
char	**find_fd(char **str, t_node *node, t_env *e);

/* parsing_util.c */
int		find_flag(char *av, char flag);
int		find_next_quote(char *av, int idx, char flag);
void	util_init(t_util *util);
int		ft_max(int a, int b);
int		get_flagcnt(char *av);

/* parsing_path.c*/
void	find_path(char *cmd, t_env *env, t_node *node);
void	get_path(char **path, t_node *node, char *cmd);

/* parsing.c */
char	***parsing(char *av);
char	**split_flag(char *av, int len, char flag);
char	*save_in(char *av, t_util *util);
int		find_other(char *av, int idx);

/* ↓↓↓↓↓ ======== EXEC ======== ↓↓↓↓↓ */
/* builtin */
void	ft_cat(t_node *node);
void	ft_cd(t_node *node);
void	ft_echo(t_node *node);
void	ft_env(t_env *head_env);
void	ft_exit(t_node *node);
void	ft_export(t_env *env, t_node *node);
void	ft_pwd(t_node *node);
void	ft_unset(t_node *node);

/* env */
t_env	*create_node_env(const char *cmd, const char *key, const char *value);
void	append_node_env(t_env **head, t_env *new_node);
t_env	*env_array_to_list(t_env *head, char **envp);
char	**env_list_to_array(t_env *head_env);
int		count_env(t_env *head_env);
void	free_env_list(t_env *head);

/* exec */
int		is_builtin(t_node *node);
int		exec_builtin(t_env *env, t_node *node);
int		run_cmd(t_env *env, t_node *node);
void	fork_process(t_env *env, t_node *node, int node_cnt);
void	wait_process(int cnt);
void	close_pipe(int *fd);
void	redirect_io(int in_fd, int out_fd);
int		count_node(t_node *node);
void	head_env_chk(t_env *head_env, int i);
void	print_env_list(t_env *head_env);

/* utils */
void	ft_free(void **target);
void	ft_free_2d(char **str);
void	print_node_details(t_node *node);
void	print_linked_list(t_node *head);
int		ft_strcmp(const char *s1, const char *s2);
void    *ft_realloc(void *ptr, int original_size, int new_size);
#endif
