NAME_CLIENT	= client
NAME_SERVER	= server
SRCS_C		= client.c
OBJS_C		= $(SRCS_C:.c=.o)
SRCS_S		= server.c
OBJS_S		= $(SRCS_S:.c=.o)
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
TESTCFLAGS	= -g -fsanitize=address -fsanitize=undefined
ARFLAGS		= rcs

all		:	$(NAME)

$(NAME)	:	$(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT)	: $(OBJS_C)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_C) 

$(NAME_CLIENT)	: $(OBJS_C)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_S) 

clean	:
	$(RM) $(OBJS)
	$(MAKE) clean -C ./libft

clean_local	:
	$(RM) $(OBJS)

fclean	:	clean
	$(RM) $(NAME)
$(MAKE) fclean -C ./libft

fclean_local	: clean_local
	$(RM) $(NAME)

re		:	fclean_local all

test	: $(NAME)
	./pipex

.PHONY	:	clean fclean clean_local fclean_local re all test
