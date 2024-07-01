CC = gcc

NAME = ft_traceroute

SDIR = ./srcs/
ODIR = ./objs/
LDIR = ./libs/libft/
LIBFT = $(LDIR)libft.a

CFLAGS = -Wall -Werror -Wextra

SRCS =	$(SDIR)/ft_traceroute.c \
		$(SDIR)/parser.c \
		$(SDIR)/utils.c \
		$(SDIR)/sockets.c \

OBJS = $(patsubst $(SDIR)%.c, $(ODIR)%.o, $(SRCS))

all: $(NAME)

.PHONY: all clean fclean re make_libft clean_libft fclean_libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -o $(NAME) $(LIBFT)

$(ODIR)%.o: $(SDIR)%.c | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)

$(LIBFT): $(LDIR)/*.c $(LDIR)/*.h
	$(MAKE) -C $(LDIR)

make_libft:
	make -C libs/libft

clean: clean_libft
	rm -f $(OBJS)
	rm -rf ./objs

clean_libft:
	make clean -C libs/libft

fclean: clean fclean_libft
	rm -f $(NAME)

fclean_libft:
	make fclean -C libs/libft

re: fclean all
