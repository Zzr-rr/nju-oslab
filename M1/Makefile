CC = gcc
CFLAGS = -Wall -Wextra -std=c11

rpstree: rpstree.o utils.o
	${CC} ${CFLAGS} -o rpstree rpstree.o utils.o

rpstree.o:
	${CC} ${CFLAGS} -c rpstree.c

utils.o:
	${CC} ${CFLAGS} -c utils.c

clean:
	rm -rf rpstree.o utils.o

build: rpstree clean

run: rpstree 
