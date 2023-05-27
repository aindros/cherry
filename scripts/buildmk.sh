#!/bin/sh

MAKEFILE=Makefile
SRC_DIR=src
BUILD_DIR=build
DIST_DIR=$BUILD_DIR/dist

# Start composing the Makefile

# Build OBJ variable
for i in `find ${SRC_DIR} -name '*.c'`; do
	OBJ=$OBJ`printf "%s " $i | sed -E "s|${SRC_DIR}(.*)\.c|$\{BUILD_DIR\}\1\.o|g"`
done

cat <<EOF > ${MAKEFILE}
# See LICENSE file for copyright and license details.

include config.mk

BUILD_DIR = ${BUILD_DIR}
DIST_DIR  = ${DIST_DIR}
OBJ       = $OBJ
INCLUDES != find $SRC_DIR -name '*.h'

all: \${PROFILE}

dist: all
	mkdir -p \${DIST_DIR}/include/cherry
	cp \${BUILD_DIR}/release/static/\${LIBNAME:=.a} \${DIST_DIR}/
	cp \${BUILD_DIR}/release/shared/\${LIBNAME:=.so} \${DIST_DIR}/
	cp \${INCLUDES} \${DIST_DIR}/include/cherry

debug: debug-static debug-shared

release: static shared

static:
	@make BUILD_DIR=\${BUILD_DIR}/release/static \${BUILD_DIR}/release/static/\${LIBNAME:=.a}

shared:
	@make BUILD_DIR=\${BUILD_DIR}/release/shared OPT="\${OPT} -fPIC" \${BUILD_DIR}/release/shared/\${LIBNAME:=.so}

debug-static:
	@make BUILD_DIR=\${BUILD_DIR}/debug/static OPT=-g \${BUILD_DIR}/debug/static/\${LIBNAME:=.a}

debug-shared:
	@make BUILD_DIR=\${BUILD_DIR}/debug/shared OPT="-g -fPIC" \${BUILD_DIR}/debug/shared/\${LIBNAME:=.so}

\${BUILD_DIR}:
	@mkdir -p \$@

\${BUILD_DIR}/\${LIBNAME:=.so}: \${BUILD_DIR} \${OBJ}
	\${CC} \${LFLAGS} -shared \${OBJ} -o \$@

\${BUILD_DIR}/\${LIBNAME:=.a}: \${BUILD_DIR} \${OBJ}
	ar rcs \$@ \${OBJ}

clean-obj:
	rm -rf ${OBJ}

clean:
	rm -rf \${BUILD_DIR}
	rm -f *.core

EOF

# Targets for object files
for i in `find ${SRC_DIR} -name '*.c'`; do
	target=`echo $i | sed -E "s|${SRC_DIR}(.*)\.c|$\{BUILD_DIR\}\1\.o|g"`
cat <<EOF >> ${MAKEFILE}
$target: $i
	\${CC} \${CFLAGS} -c \$> -o \$@

EOF
done


