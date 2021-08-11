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

LIBFT	= $(LIBDIR)/libft.a

all		: $(CLIENT) $(SERVER)

$(LIBFT) :
	@echo "Making libft"
	@make -C $(LIBDIR) all

$(CLIENT) : $(LIBFT) $(COBJS) $(UOBJS)
	@echo "Creating $(CLIENT)"
	@$(CC) $(CFLAGS) $(COBJS) $(UOBJS) $(LIBFT) -o $@

$(SERVER) : $(LIBFT) $(SOBJS) $(UOBJS)
	@echo "Creating $(SERVER)"
	@$(CC) $(CFLAGS) $(SOBJS) $(UOBJS) $(LIBFT) -o $@

bonus	: all

clean	:
	@make -C $(LIBDIR) clean
	@$(RM) $(SOBJS) $(COBJS) $(UOBJS)

fclean	: clean
	@make -C $(LIBDIR) fclean
	@$(RM) $(CLIENT) $(SERVER)

re		: fclean all

.PHONY	: all bonus clean fclean re