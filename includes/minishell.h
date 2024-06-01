/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:22:33 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 16:45:34 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0

# define STDIN 0
# define STDOUT 1

# define MAX_LL 9223372036854775807LL

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
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
	int	prev_errnum;
}t_util;

typedef struct s_env
{
	char			*cmd;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_envutil
{
	char	*key;
	char	*value;
	char	*tmp;
}	t_envutil;

typedef struct s_stdio
{
	int	stdin_backup;
	int	stdout_backup;
}	t_stdio;

int		g_signal_error;

/* PARSER */

/* minishell.c */
void		readline_minishell(t_env **env);
int			minishell(char *av, t_env **env);
int			parsing_minishell(t_node **head, char **str, t_env *env, int p_e);

/* parsing_dollar_find.c */
char		*get_word(char *av, int *idx);
int			find_dollar(char *av, t_env *env, int p_e);
int			is_print(char s);
void		jump_next_word(char *av, t_util *u);
int			find_dollar_two(char *av, t_env *env, int p_e, t_util *u);

/* parsing_dollar_put.c */
void		put_str(char *str, char *av, int *a_idx, int *s_idx);
void		put_word(char *av, char *word, int *idx);
void		put_env(char *str, char *av, t_env *env, t_util *u);
void		put_change_dollar(char *av, char *str, t_env *env, t_util *u);
void		put_dollar(char *av, char *str, t_util *u);

/* parsing_delquote.c */
char		*del_quote(char *av);
char		**split_space(char *av, int len);
char		**check_cmd(char **av);
void		del_q(char *av, char *str, t_util *u);
int			split_space_main(char *tmp, char **str, t_util *u);

/* parsing_dollar.c */
char		*check_dollar(char *av, t_env *env, int p_e);
char		*change_dollar(char *av, t_env *env, int env_len, int p_e);

/* parsing_error.c*/
int			get_numlen(int num);
void		put_errno(char *str, int p_e, t_util *u);
int			file_error(void);
void		notfile_error(char *file);
char		*malloc_fail(void);

/* parsing_find.c */
int			find_flag(char *av, char flag);
int			find_env(char *av, int *idx, t_env *env);
int			find_next_quote(char *av, int idx, char flag);
int			find_other(char *av, int idx);
int			find_cut(char *av);

/* parsing_free.c */
void		free_str(char **str);
int			free_str_three(char ***str);
void		free_node(t_node *head);
int			count_str(char **str);
char		**free_all(char **cmd, int idx);

/* parsing_heredoc_dollar.c*/
void		putin_doublequote(char *av, char *str, t_env *env, t_util *u);
char		*heredoc_change_dollar(char *av, t_env *env, int env_len, int p_e);
void		heredoc_change_dollar_two(char *av, char *str, int p_e, t_util *u);
int			heredoc_find_dollar(char *av, t_env *env, int p_e);
int			in_doublequote(char *av, int p_e, t_env *env, t_util *u);

/* parsing_heredoc.c */
void		heredoc_infile(char **str, int *i, t_node *node, t_env *env);
void		heredoc_process(char **str, int *i, t_node *node, t_env *env);
char		*heredoc_check_dollar(char *av, t_env *env, t_node *node);
int			heredoc_readline(char *av, char *str, t_node *node, t_env *env);

/* parsing_in_pipe.c */
int			parsing_in_pipe(char *av, t_node *node, t_env *env, int p_e);
char		*add_space(char *av);

/* paring_infd.c */
void		is_infd(char **str, t_util *u, t_node *node, t_env *env);
char		*file_check_dollar(char *av, t_env *env, int p_e);
int			check_file(char *str);

/* parsing_node.c */
int			save_in_node(t_node *node, char **cmd);
t_node		*create_node(int p_e);
void		append_node(t_node **head, t_node *new_node);
void		util_init(t_util *util);
int			is_path(char *cmd);

/* parsing_outfd.c */
void		is_outfd(char **str, t_util *u, t_node *node, t_env *env);
int			get_cmd(char **cmd, t_util *u, char **str);
char		**find_fd(char **str, t_node *node, t_env *e, int p_e);

/* parsing_util.c */
int			ft_max(int a, int b);
int			get_flagcnt(char *av);
int			check_line(char **str);
int			check_pipeline(char ***str);
int			check_file_two(char *str, t_util *u);

/* parsing_path.c*/
int			find_path(char *cmd, t_env *env, t_node *node);
int			check_file_or_cmd(char *cmd, char *tmp);

/* parsing.c */
char		***parsing(char *av);
char		**split_flag(char *av, int len, char flag);
char		*save_in(char *av, t_util *util);
int			split_by_pipe(char **str_smc, char ***str_pipe);
int			split_flag_save(char *av, char **str, t_util *u, char flag);

/* EXEC */

/* builtin/ft_cd */
void		ft_cd(t_env **env, t_node *node);
void		ft_cd_error(int check, char *path);
int			update_pwd(t_env **env, char *cur_path);
int			update_oldpwd(t_env **env, char *cur_path);
t_env		*is_env(t_env *env, char *key);

/* builtin/ft_echo */
void		ft_echo(t_node *node);

/* builtin/ft_env */
void		ft_env(t_env *env, t_node *node);

/* builtin/ft_exit */
void		ft_exit(t_env *env, t_node *node, pid_t pid);
int			is_numeric(char *str);
long long	check_first_arg(t_node *node, int *error);

/* builtin/ft_export */
void		ft_export(t_env **env, t_node *node);
int			export_witharg(t_env **env, t_node *node);
int			renew_env(t_env *cur, char *cmd, char *value);
int			add_env(t_env **env, char *cmd, char *key, char *value);
int			ft_export_error(int error, char *path);
int			export_withoutarg(t_env *env);
int			is_key(char *key);
int			is_value(char *value);

/* builtin/ft_pwd */
void		ft_pwd(t_env *env, t_node *node);

/* builtin/ft_unset */
void		ft_unset(t_env **env, t_node *node);

/* env/env_init.c */
void		set_env_list(t_env **env, char **envp);
char		**env_list_to_array(t_env *env);

/* env/env_util.c */
t_env		*create_node_env(char *cmd, char *key, char *value);
void		append_node_env(t_env **head, t_env *new_node);
int			add_env_to_list(t_env **head, char *ori, char *key, char *value);
void		parse_env_str(char *env_str, char **key, char **value);
void		free_env_list(t_env *head);

/* exec/builtin.c */
int			is_builtin(t_node *node);
int			exec_builtin(t_env **env, t_node *node, pid_t pid);

/* exec/exe.c */
int			ft_execve(t_env **env, t_node *node,  pid_t pid);
void		is_inchild(char *cmd);

/* exec/process.c */
void		fork_process(t_env **env, t_node *node, int node_cnt);
int			processing(t_env **env, t_node *head);

/* exec/process_util1.c */
int			count_node(t_node *node);
void		redirect_io(int in_fd, int out_fd);
void		wait_process(int cnt);
void		close_pipe(int *fd);

/* exec/process_util2.c */
void		save_stdio(t_stdio *backup);
void		restore_stdio(t_stdio *backup);

/* util/custom_handler.c */
void		sig_handler(int signal);
void		child_handler(int signal);
void		heredoc_handler(int signal);

/* util/ft_arrlen_2d.c */
int			ft_arrlen_2d(char **array);

/* util/ft_free.c */
void		ft_free(void **target);
void		ft_free_2d(char **str);

/* ft_strcmp.c */
int			ft_strcmp(const char *s1, const char *s2);

/* ft_strtoll.c */
long long	ft_strtoll(const char *str, int *signal);

/* print_error.c */
int			print_error(void);
void		syntax_error(char *str, t_node *node);

#endif
