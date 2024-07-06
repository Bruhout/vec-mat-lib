CC = gcc
SRC_DIR = src
BUILD_DIR = build
C_FLAGS = -Wall -Wextra -lm

linalg.a: ${BUILD_DIR}/mat.o ${BUILD_DIR}/vec.o ${BUILD_DIR}/err.o
	ar rcs linalg.a ${BUILD_DIR}/mat.o ${BUILD_DIR}/vec.o ${BUILD_DIR}/err.o

${BUILD_DIR}/mat.o: ${SRC_DIR}/mat.c
	${CC} -o ${BUILD_DIR}/mat.o ${SRC_DIR}/mat.c -c ${C_FLAGS}

${BUILD_DIR}/vec.o: ${SRC_DIR}/vec.c
	${CC} -o ${BUILD_DIR}/vec.o ${SRC_DIR}/vec.c -c ${C_FLAGS}

${BUILD_DIR}/err.o: ${SRC_DIR}/err.c
	${CC} -o ${BUILD_DIR}/err.o ${SRC_DIR}/err.c -c ${C_FLAGS}

test : ${SRC_DIR}/unit-tests.c linalg.a
	gcc -o test ${SRC_DIR}/unit-tests.c linalg.a ${C_FLAGS}