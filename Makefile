NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = src/main.c src/coder.c src/dongle.c src/monitor.c src/parser.c src/parser_helper.c src/scheduler.c src/simulation.c src/time.c src/logger.c
OBJ = src/main.o src/coder.o src/dongle.o src/monitor.o src/parser.o src/parser_helper.o src/scheduler.o src/simulation.o src/time.o src/logger.o

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re