DIR_INC = ./inc
DIR_SRC = ./src
LIB = ./src/lib
DIR_OBJ = ./obj
DIR_BIN = ./bin
DEVICE = ./src/device

CHECK := $(shell test -d ${DIR_INC} || mkdir -p ${DIR_INC})
CHECK := $(shell test -d ${DIR_SRC} || mkdir -p ${DIR_SRC})
CHECK := $(shell test -d ${DIR_OBJ} || mkdir -p ${DIR_OBJ})
CHECK := $(shell test -d ${DIR_BIN} || mkdir -p ${DIR_BIN})

SRC = $(wildcard ${DIR_SRC}/*.c   ${LIB}/*.c ${DEVICE}/*.c)
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC}))

TARGET = main

STRIP =  arm-linux-gnueabihf-strip

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = arm-linux-gnueabihf-gcc
CFLAGS = -g -Wall -I${DIR_INC}

all: main 

main:$(BIN_TARGET)
${BIN_TARGET}:${OBJ}
	 $(CC) $(OBJ)  -o $@ -lpthread -static
	 $(STRIP) $@

#./src 下.c文件编译
${DIR_OBJ}/%.o:${DIR_SRC}/%.c ${DIR_INC}/%.h
	$(CC) $(CFLAGS) -c  $< -o $@ 

#./src/lib 文件下.c编译
${DIR_OBJ}/%.o:${LIB}/%.c 
	$(CC) $(CFLAGS) -c  $< -o $@ 

#./src/devcice 文件下.c编译
${DIR_OBJ}/%.o:${DEVICE}/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ 



.PHONY:clean
clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
	find ${DIR_BIN} -name ${TARGET} -exec rm -rf {} \;

upload_main:
	./upload_main.sh
