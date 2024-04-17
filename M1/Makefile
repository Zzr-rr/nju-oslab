CC = gcc
CFLAGS = -Wall -Wextra
VALFLAGS = --tool=memcheck --leak-check=full
INCLUDES = includes/
SRC = src/

rpstree: rpstree.o utils.o processtree.o output.o
	${CC} ${CFLAGS} -o rpstree rpstree.o utils.o processtree.o output.o

utils.o:
	${CC} ${CFLAGS} -c ${SRC}utils.c
processtree.o:
	${CC} ${CFLAGS} -c ${SRC}processtree.c
output.o:
	${CC} ${CFLAGS} -c ${SRC}output.c

rpstree.o:
	${CC} ${CFLAGS} -c rpstree.c

check: rpstree clean
	valgrind ${VALFLAGS} ./rpstree

clean:
	rm -rf rpstree.o utils.o processtree.o output.o

build: rpstree clean

run: rpstree 
