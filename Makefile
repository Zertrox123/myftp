
SRC     =	src/main.c	\
			src/server_auth.c	\
			src/server_init.c	\
			src/server_run.c	\
			src/server_commands.c	\
			src/commands/cdup.c	\
			src/commands/cwd.c	\
			src/commands/pasv.c	\
			src/commands/pwd.c	\
			src/commands/type.c	\
			src/commands/list.c	\
			src/commands/data.c	\
			src/commands/port.c	\
			src/commands/retr.c	\
			src/commands/stor.c	\
			src/commands/delete.c

OBJ     = $(SRC:.c=.o)

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I./include

NAME    = myftp

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
