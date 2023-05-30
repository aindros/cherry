# See LICENSE file for copyright and license details.

NAME = tests
CC   = cc
SRC != find * -name '*.c'
OBJ  = ${SRC:.c=.o}

LIB  = x11 utils log

CFLAGS != pkg-config --cflags ${LIB}
LFLAGS != pkg-config --libs ${LIB}

CFLAGS += -I../build/include
LFLAGS += ../build/debug/static/libcherry.a

all: init-lib ${OBJ} ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

init-lib:
	cd ../ && make debug-static

${NAME}:
	${CC} ${LFLAGS} ${OBJ} -o $@
