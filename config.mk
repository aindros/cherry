# See LICENSE file for copyright and license details.

NAME = cherry

CC   = cc
SRC != find src -name '*.c'
OBJ  = ${SRC:.c=.o}
LIB  = x11 utils
STD  = c11
#WRN  = -Wall -Werror

CFLAGS != pkg-config --cflags ${LIB}
LFLAGS != pkg-config --libs ${LIB}

CFLAGS += -std=${STD} ${WRN} ${OPT}
