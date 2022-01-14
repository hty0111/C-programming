CC  = i686-w64-mingw32-gcc
OBJ      = ./bin/client/dataDeal.o ./bin/client/interface.o ./bin/client/menufunctions.o ./bin/client/mongoose.o ./bin/client/netClient.o ./bin/client/cJSON.o ./bin/client/exceptio.o ./bin/client/genlib.o ./bin/client/graphics.o ./bin/client/random.o ./bin/client/simpio.o ./bin/client/strlib.o ./bin/client/imgui.o
LINKOBJ  = ./bin/client/dataDeal.o ./bin/client/interface.o ./bin/client/menufunctions.o ./bin/client/mongoose.o ./bin/client/netClient.o ./bin/client/cJSON.o ./bin/client/exceptio.o ./bin/client/genlib.o ./bin/client/graphics.o ./bin/client/random.o ./bin/client/simpio.o ./bin/client/strlib.o ./bin/client/imgui.o
LIBS     = -lwsock32 -lm -lgdi32
INCS =  -I ./netClient  -I ./dataDeal  -I ./GUI  -I ./library/mongoose  -I ./library/cJSON  -I ./library/libgraphics  -I ./library/simpleGUI 
BIN      = ./bin/client/bookClient.exe
CFLAGS   = $(INCS) -std=c99 -O2
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom run

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)

./bin/client/dataDeal.o: ./dataDeal/dataDeal.c
	$(CC) -c ./dataDeal/dataDeal.c -o ./bin/client/dataDeal.o $(CFLAGS)

./bin/client/interface.o: ./GUI/interface.c
	$(CC) -c ./GUI/interface.c -o ./bin/client/interface.o $(CFLAGS)

./bin/client/menufunctions.o: ./GUI/menufunctions.c
	$(CC) -c ./GUI/menufunctions.c -o ./bin/client/menufunctions.o $(CFLAGS)

./bin/client/mongoose.o: ./library/mongoose/mongoose.c
	$(CC) -c ./library/mongoose/mongoose.c -o ./bin/client/mongoose.o $(CFLAGS)

./bin/client/netClient.o: ./netClient/netClient.c
	$(CC) -c ./netClient/netClient.c -o ./bin/client/netClient.o $(CFLAGS)

./bin/client/cJSON.o: ./library/cJSON/cJSON.c
	$(CC) -c ./library/cJSON/cJSON.c -o ./bin/client/cJSON.o $(CFLAGS)

./bin/client/exceptio.o: ./library/libgraphics/exceptio.c
	$(CC) -c ./library/libgraphics/exceptio.c -o ./bin/client/exceptio.o $(CFLAGS)

./bin/client/genlib.o: ./library/libgraphics/genlib.c
	$(CC) -c ./library/libgraphics/genlib.c -o ./bin/client/genlib.o $(CFLAGS)

./bin/client/graphics.o: ./library/libgraphics/graphics.c
	$(CC) -c ./library/libgraphics/graphics.c -o ./bin/client/graphics.o $(CFLAGS)

./bin/client/random.o: ./library/libgraphics/random.c
	$(CC) -c ./library/libgraphics/random.c -o ./bin/client/random.o $(CFLAGS)

./bin/client/simpio.o: ./library/libgraphics/simpio.c
	$(CC) -c ./library/libgraphics/simpio.c -o ./bin/client/simpio.o $(CFLAGS)

./bin/client/strlib.o: ./library/libgraphics/strlib.c
	$(CC) -c ./library/libgraphics/strlib.c -o ./bin/client/strlib.o $(CFLAGS)

./bin/client/imgui.o: ./library/simpleGUI/imgui.c
	$(CC) -c ./library/simpleGUI/imgui.c -o ./bin/client/imgui.o $(CFLAGS)

run :
	wine $(BIN)

prepare :
	sudo apt-get update
	sudo apt-get install mingw-w64*
	sudo apt-get install wine-development