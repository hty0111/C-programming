CC       = gcc.exe
OBJ      = ./bin/server/Windows/dataStore.o ./bin/server/Windows/identify.o ./bin/server/Windows/cJSON.o ./bin/server/Windows/mongoose.o ./bin/server/Windows/sqlite3.o ./bin/server/Windows/netServer.o
LINKOBJ  = ./bin/server/Windows/dataStore.o ./bin/server/Windows/identify.o ./bin/server/Windows/cJSON.o ./bin/server/Windows/mongoose.o ./bin/server/Windows/sqlite3.o ./bin/server/Windows/netServer.o
LIBS     = -L"C:/Program Files (x86)/Dev-Cpp/MinGW64/lib" -L"C:/Program Files (x86)/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib" -static-libgcc -lwsock32
INCS     = -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/x86_64-w64-mingw32/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/lib/gcc/x86_64-w64-mingw32/4.9.2/include" -I"./library/cJSON" -I"./library/mongoose" -I"./library/sqlite3" -I"./dataStore" -I"./identify" -I"./netServer"
BIN      = ./bin/server/Windows/bookServer.exe
CXXFLAGS = $(CXXINCS) 
CFLAGS   = $(INCS) -std=c99 -O2
RM       = rm.exe -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)

./bin/server/Windows/dataStore.o: ./dataStore/dataStore.c
	$(CC) -c ./dataStore/dataStore.c -o ./bin/server/Windows/dataStore.o $(CFLAGS)

./bin/server/Windows/identify.o: ./identify/identify.c
	$(CC) -c ./identify/identify.c -o ./bin/server/Windows/identify.o $(CFLAGS)

./bin/server/Windows/cJSON.o: ./library/cJSON/cJSON.c
	$(CC) -c ./library/cJSON/cJSON.c -o ./bin/server/Windows/cJSON.o $(CFLAGS)

./bin/server/Windows/mongoose.o: ./library/mongoose/mongoose.c
	$(CC) -c ./library/mongoose/mongoose.c -o ./bin/server/Windows/mongoose.o $(CFLAGS)

./bin/server/Windows/sqlite3.o: ./library/sqlite3/sqlite3.c
	$(CC) -c ./library/sqlite3/sqlite3.c -o ./bin/server/Windows/sqlite3.o $(CFLAGS)

./bin/server/Windows/netServer.o: ./netServer/netServer.c
	$(CC) -c ./netServer/netServer.c -o ./bin/server/Windows/netServer.o $(CFLAGS)