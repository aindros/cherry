# See LICENSE file for copyright and license details.

include config.mk

BUILD_DIR = build
DIST_DIR  = dist
OBJ       = ${BUILD_DIR}/cherry.o ${BUILD_DIR}/main.o ${BUILD_DIR}/window.o ${BUILD_DIR}/application.o ${BUILD_DIR}/event.o ${BUILD_DIR}/widget.o 
INCLUDES != find src -name '*.h'

all: static shared

${DIST_DIR}: all
	mkdir -p $@/include/cherry
	cp ${BUILD_DIR}/release/static/${LIBNAME:=.a} $@/
	cp ${BUILD_DIR}/release/shared/${LIBNAME:=.so} $@/
	cp ${INCLUDES} $@/include/cherry

debug: debug-static debug-shared

static:
	@make BUILD_DIR=${BUILD_DIR}/release/static ${BUILD_DIR}/release/static/${LIBNAME:=.a}

shared:
	@make BUILD_DIR=${BUILD_DIR}/release/shared OPT="${OPT} -fPIC" ${BUILD_DIR}/release/shared/${LIBNAME:=.so}

debug-static:
	@make BUILD_DIR=${BUILD_DIR}/debug/static OPT=-g ${BUILD_DIR}/debug/static/${LIBNAME:=.a}

debug-shared:
	@make BUILD_DIR=${BUILD_DIR}/debug/shared OPT="-g -fPIC" ${BUILD_DIR}/debug/shared/${LIBNAME:=.so}

${BUILD_DIR}:
	@mkdir -p $@

${BUILD_DIR}/${LIBNAME:=.so}: ${BUILD_DIR} ${OBJ}
	${CC} ${LFLAGS} -shared ${OBJ} -o $@

${BUILD_DIR}/${LIBNAME:=.a}: ${BUILD_DIR} ${OBJ}
	ar rcs $@ ${OBJ}

clean-obj:
	rm -rf ${BUILD_DIR}/cherry.o ${BUILD_DIR}/main.o ${BUILD_DIR}/window.o ${BUILD_DIR}/application.o ${BUILD_DIR}/event.o ${BUILD_DIR}/widget.o 

clean:
	rm -rf ${BUILD_DIR}
	rm -f *.core

${BUILD_DIR}/cherry.o: src/cherry.c
	${CC} ${CFLAGS} -c $> -o $@

${BUILD_DIR}/main.o: src/main.c
	${CC} ${CFLAGS} -c $> -o $@

${BUILD_DIR}/window.o: src/window.c
	${CC} ${CFLAGS} -c $> -o $@

${BUILD_DIR}/application.o: src/application.c
	${CC} ${CFLAGS} -c $> -o $@

${BUILD_DIR}/event.o: src/event.c
	${CC} ${CFLAGS} -c $> -o $@

${BUILD_DIR}/widget.o: src/widget.c
	${CC} ${CFLAGS} -c $> -o $@

