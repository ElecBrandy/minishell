# Complie
CC = cc
# CFLAGS = -Wall -Wextra -Werror # Norm
CFLAGS = -g -fsanitize=address # catch segfault error
# CFLAGS = -g # if with (export MallocStackLogging=1) -> catch memory leaks

# Readline - Cluster ver
COMFILE_FLAGS = -lreadline -L/usr/local/lib
OBJ_FLAGS = -I/usr/local/include/readline

# Directories
LIB_DIR = libft/
INC_DIR = includes/

# Includes
INC = -I$(INC_DIR)
LIB = -L$(LIB_DIR) -lft

# Sources
SRCS_P = \
	srcs/parser/parsing_delquote.c  \
	srcs/parser/parsing_dollar_util.c	\
	srcs/parser/parsing_dollar.c	\
	srcs/parser/parsing_fd.c        \
	srcs/parser/parsing_free.c      \
	srcs/parser/parsing_heredoc.c	\
	srcs/parser/parsing_in_pipe.c   \
	srcs/parser/parsing_node.c      \
	srcs/parser/parsing_utils.c     \
	srcs/parser/parsing.c           \

SRCS_E = \
	srcs/builtin/ft_cd.c        \
	srcs/builtin/ft_pwd.c       \
	srcs/builtin/ft_env.c       \
	srcs/builtin/ft_exit.c      \
	srcs/builtin/ft_echo.c      \
	srcs/builtin/ft_unset.c     \
	srcs/builtin/ft_export.c    \
	\
	srcs/env/env_init.c			\
	srcs/env/env_util.c			\
	\
	srcs/exec/exec.c            \
	srcs/exec/builtin.c         \
	srcs/exec/process.c         \
	srcs/exec/process_utils.c   \
	\
	srcs/utils/ft_free.c		\
	srcs/utils/tmp.c			\
	srcs/utils/ft_strcmp.c

SRCS_M = \
	srcs/minishell.c

SRCS = $(SRCS_E) $(SRCS_P) $(SRCS_M)

# Objects
OBJS = $(SRCS:.c=.o)

# Commands
RM = rm -rf
TOUCH = touch
MAKE = make

# Name
NAME = minishell

# Rules
all : $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIB_DIR) --silent
	$(CC) $(CFLAGS) $(COMFILE_FLAGS) -o $@ $^ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(OBJ_FLAGS) -c -o $@ $< $(INC)

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

.PHONY: all clean fclean re
