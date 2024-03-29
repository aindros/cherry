# See LICENSE file for copyright and license details.

include config.mk

BUILD_DIR = build
DIST_DIR  = build/dist
OBJ       = ${BUILD_DIR}/cherry.o ${BUILD_DIR}/main.o ${BUILD_DIR}/window.o ${BUILD_DIR}/application.o ${BUILD_DIR}/event.o ${BUILD_DIR}/widget.o 
INCLUDES != find src -name '*.h'

all: ${PROFILE}

dist: all
	mkdir -p ${DIST_DIR}/include/cherry
	cp ${BUILD_DIR}/release/static/${LIBNAME:=.a} ${DIST_DIR}/
	cp ${BUILD_DIR}/release/shared/${LIBNAME:=.so} ${DIST_DIR}/
	cp ${INCLUDES} ${DIST_DIR}/include/cherry

debug: debug-static debug-shared copy-includes

release: static shared copy-includes

static:
	@make BUILD_DIR=${BUILD_DIR}/release/static ${BUILD_DIR}/release/static/${LIBNAME:=.a}

shared:
	@make BUILD_DIR=${BUILD_DIR}/release/shared OPT="${OPT} -fPIC" ${BUILD_DIR}/release/shared/${LIBNAME:=.so}

debug-static:
	@make BUILD_DIR=${BUILD_DIR}/debug/static OPT=-g ${BUILD_DIR}/debug/static/${LIBNAME:=.a}

copy-includes:
	@mkdir -p ${BUILD_DIR}/include/cherry
	@cp ${INCLUDES} ${BUILD_DIR}/include/cherry

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
	rm -f test/tests

tests: debug
	cd test && make
	test/tests

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

