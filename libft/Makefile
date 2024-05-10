# Compile
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Includes
INC = libft.h

# Sources
SRCS_PART1 = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c
SRCS_PART2 = ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_find_quotes.c ft_strldup.c
SRCS_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
SRCS = $(SRCS_PART1) $(SRCS_PART2) $(SRCS_BONUS)

# Objects
OBJS = $(SRCS:.c=.o)

# Name
NAME = libft.a

# Commands
RM = rm -f
AR = ar rc
TOUCH = touch
MAKE = make

# Rules
all: $(NAME)
bonus: make_bonus

$(NAME): make_man

make_man: $(OBJS)
	$(AR) $(NAME) $^
	$(TOUCH) make_man

clean:
	$(RM) $(OBJS)

fclean:
	$(MAKE) clean
	$(RM) $(NAME)
	$(RM) make_man

re:
	$(MAKE) fclean
	$(MAKE) all

%.o : %.c
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

.PHONY: all clean fclean re bonus
