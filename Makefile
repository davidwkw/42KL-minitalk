CLIENT	= client

SERVER	= server

USRCS	= minitalk_utils.c

CSRCS 	= client.c

SSRCS	= server.c

COBJS	= $(CSRCS:.c=.o)

SOBJS	= $(SSRCS:.c=.o)

UOBJS	= $(USRCS:.c=.o)

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -I.

LIBDIR	= ./libft

LIBFT	= $(LIBFTDIR)/libft.a

all		: $(CLIENT) $(SERVER)

$(LIBFT) :
	@echo "Making libft"
	@make -C $(LIBDIR)

$(CLIENT) : $(COBJS) $(UOBJS) $(LIBFT)
	@echo "Creating $(CLIENT)"
	@$(CC) $(CFLAGS) -o $(COBJS) $(UOBJS) $(LIBFT)

$(SERVER) : $(SOBJS) $(UOBJS) $(LIBFT)
	@echo "Creating $(SERVER)"
	@$(CC) $(CFLAGS) -o $(SOBJS) $(UOBJS) $(LIBFT)

bonus	: all

clean	:
	@make -C $(LIBDIR) clean
	@$(RM) $(SOBJS) $(COBJS) $(UOBJS)

fclean	: clean
	@make -C $(LIBDIR) fclean
	@$(RM) $(CLIENT) $(SERVER)

re		: fclean all

.PHONY	: all bonus clean fclean re