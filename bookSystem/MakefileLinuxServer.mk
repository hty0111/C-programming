CC = gcc
CFLAGS =  -O2 -std=c99
INCS = -I ./dataStore -I ./identify -I ./library/sqlite3 -I ./library/cJSON -I ./library/mongoose -I ./netServer
LIBS = -lm -lpthread -ldl
EXE = ./bin/server/Linux/bookServer
SRC = $(wildcard ./dataStore/*.c ./identify/*.c ./library/sqlite3/*.c ./library/cJSON/*.c ./library/mongoose/*.c ./netServer/*.c)
OBJ = $(SRC:%.c=%.o)
RM = rm -rf

.PHONY: clean run all

all : ${EXE}

${EXE} : ${OBJ}
	${CC} -o $@ $^ ${INCS} ${LIBS} ${CFLAGS}
%.o : %.c
	${CC} -c -o $@ $< ${INCS} ${CFLAGS}

clean:
	${RM} ${OBJ} ${EXE}

run:
	${EXE}