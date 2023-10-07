NAME		= name
NAME_CLIENT	= client
NAME_SERVER	= server
SRCS_CLIENT	= client.c
OBJS_CLIENT	= $(SRCS_CLIENT:.c=.o)
SRCS_SERVER	= server.c
OBJS_SERVER	= $(SRCS_SERVER:.c=.o)
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

all		:	$(NAME)

$(NAME)	: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT)	:	$(OBJS_CLIENT)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(OBJS_CLIENT) libft/libft.a -o $(NAME_CLIENT)

$(NAME_SERVER)	:	$(OBJS_SERVER)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(OBJS_SERVER) libft/libft.a -o $(NAME_SERVER)

clean	:
	$(RM) $(OBJS_CLIENT)
	$(RM) $(OBJS_SERVER)
	$(MAKE) clean -C libft

fclean	:	clean
	$(RM) $(NAME_CLIENT)
	$(RM) $(NAME_SERVER)
	$(MAKE) fclean -C libft

re		:	fclean all

.PHONY	:	clean fclean re all
