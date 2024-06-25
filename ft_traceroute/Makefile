CC = gcc

NAME = ft_traceroute

SDIR = ./srcs/
OBJDIR = ./objs/
LIBFT = ./libs/libft/libft.a

CFLAGS = -Wall -Werror -Wextra

OBJECTS = $(OBJDIR)/*.o

SRCS =	./srcs/ft_traceroute.c \
		./srcs/parser.c \
		./srcs/utils.c \
		./srcs/sockets.c \

$(NAME): $(OBJECTS) make_libft
	$(CC) $(OBJECTS) -o $(NAME) $(LIBFT)

$(OBJECTS): $(SRCS)
	$(CC) -c $(CFLAGS) $(SRCS)
	rm -rf ./objs; mkdir ./objs
	mv *.o $(OBJDIR)

all: $(NAME)

make_libft:
	make -C libs/libft

clean: clean_libft
	rm -f $(OBJECTS)
	rm -rf ./objs

clean_libft:
	make clean -C libs/libft

fclean: clean fclean_libft
	rm -f $(NAME)

fclean_libft:
	make fclean -C libs/libft

re: fclean all
