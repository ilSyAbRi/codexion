NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = src/main.c src/coder.c src/dongle.c src/monitor.c src/parser.c src/parser_helper.c  src/simulation.c src/time.c src/logger.c src/heap.c src/init_heap.c src/destroy_mutex.c
OBJ = src/main.o src/coder.o src/dongle.o src/monitor.o src/parser.o src/parser_helper.o  src/simulation.o src/time.o src/logger.o src/heap.o src/init_heap.o src/destroy_mutex.o

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re