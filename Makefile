# See LICENSE file for copyright and license details.

include config.mk

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${LFLAGS} ${OBJ} -o $@

debug:
	@make OPT=-g all

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf ${OBJ} ${NAME}
	rm -f *.core
