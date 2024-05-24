CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = get_next_line.h
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
NAME = libgnl.a

RM = rm -f
AR = ar rc
TOUCH = touch
MAKE = make

all: $(NAME)

$(NAME): make_man

make_man: $(OBJS)
	$(AR) $(NAME) $^
	$(TOUCH) .make_man

clean:
	$(RM) $(OBJS)

fclean:
	$(MAKE) clean
	$(RM) $(NAME)
	$(RM) .make_man 

re:
	$(MAKE) fclean
	$(MAKE) all

%.o : %.c
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

.PHONY: all clean fclean re bonus
