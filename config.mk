# See LICENSE file for copyright and license details.

LIBNAME = libcherry

CC   = cc
LIB  = x11 utils log
STD  = c11
OPT  = -O2 -pipe
#WRN  = -Wall -Werror

CFLAGS != pkg-config --cflags ${LIB}
LFLAGS != pkg-config --libs ${LIB}

CFLAGS += -std=${STD} ${WRN} ${OPT}
