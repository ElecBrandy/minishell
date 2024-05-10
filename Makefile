CC = cc
CFLAGS = -Wall -Wextra -Werror
COMFILE_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
OBJ_FLAGS = -I${HOME}/.brew/opt/readline/include
SRCS_PARSER = srcs/minishell.c srcs/parser/parsing.c srcs/parser/parsing_free.c srcs/parser/parsing_in_pipe.c srcs/parser/parsing_fd.c srcs/parser/parsing_utils.c srcs/parser/parsing_delquote.c
SRCS_M = \
    srcs/builtin/ft_cd.c srcs/builtin/ft_echo.c      \
    srcs/builtin/ft_env.c       \
    srcs/builtin/ft_exit.c      \
    srcs/builtin/ft_export.c    \
    srcs/builtin/ft_pwd.c       \
    srcs/builtin/ft_unset.c     \
    \
    srcs/env/env_node.c         \
    srcs/env/get_env.c          \
    \
    srcs/exec/builtin.c         \
    srcs/exec/exec.c            \
    srcs/exec/here_doc.c        \
    srcs/exec/process.c         \
    srcs/exec/redirection.c     \
    \
    srcs/utils/ft_free.c        \
    srcs/utils/node_cmd.c        \
    srcs/main.c

SRCS = $(SRCS_M) $(SRCS_PARSER)
OBJS = $(SRCS:.c=.o)

INC = -I$(INC_DIR)
LIB = -L$(LIB_DIR) -lft

NAME = minishell

LIB_DIR = libft/
INC_DIR = includes/

RM = rm -rf
TOUCH = touch
MAKE = make

all : $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIB_DIR) --silent
	$(CC) $(CFLAGS) $(COMFILE_FLAGS) -o $@ $^ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS)  $(OBJ_FLAGS) -c -o $@ $< $(INC)

clean:
	$(MAKE) -C $(LIB_DIR) clean --silent
	$(RM) $(OBJS)

fclean:
	$(MAKE) clean
	$(MAKE) -C $(LIB_DIR) fclean --silent
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus