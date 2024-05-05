CC = gcc
CFLAGS = -Wall -Wextra
VALFLAGS = --tool=memcheck --leak-check=full
INCLUDES = includes/
SRC = src/

clean: run
	rm -rf mytest

run:
	${CC} ${CFLAGS} -o mytest mytest.c && ./mytest
