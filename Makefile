CC = clang++
CFLAGS = -g -std=c++17
SRC  = $(wildcard src/**/*.cpp) $(wildcard src/*.cpp) $(wildcard src/**/**/*.cpp) $(wildcard src/**/**/**/*.cpp)
OBJ  = $(SRC:.cpp=.o)
LDFLAGS = -g
BIN = 1000th-summer

OSFLAG 				:=
ifeq ($(OS),Windows_NT)
	OSFLAG += WIN32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG += LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG += OSX
	endif
		UNAME_P := $(shell uname -p)
endif

ifeq ($(OSFLAG), LINUX)
	LDFLAGS += -lX11
endif

ifeq ($(OSFLAG), WIN32)
	BIN = 1000th-summer.exe
endif

CLEAN :=
ifeq ($(OSFLAG),WIN32)
	CLEAN = del /q /s 1000th-summer.exe *.o .fuse_ 1000th-summer.ilk 1000th-summer.pdb
else
	CLEAN = rm -rf 1000th-summer $(OBJ) .fuse_ frags
endif

all: 1000th-summer

1000th-summer: $(OBJ)
	$(CC) -o $(BIN) $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

test:
	echo $(SRC)
	echo $(OBJ)

clean:
	$(CLEAN)

os:
	echo $(OSFLAG)