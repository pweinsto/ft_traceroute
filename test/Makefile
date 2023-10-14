CC = gcc

NAME = test

SDIR = ./srcs/
OBJDIR = ./objs/

CFLAGS =# -Wall -Werror -Wextra

OBJECTS = $(OBJDIR)/*.o

SRCS =	./srcs/main.c \

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)

$(OBJECTS): $(SRCS)
	$(CC) -c $(CFLAGS) $(SRCS)
	rm -rf ./objs; mkdir ./objs
	mv *.o $(OBJDIR)


clean:
	rm -f $(OBJECTS)
	rm -rf ./objs

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

