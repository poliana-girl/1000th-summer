CC = g++
CFLAGS = -g -std=c++17 
SRC  = $(wildcard src/**/*.cpp) $(wildcard src/*.cpp) $(wildcard src/**/**/*.cpp) $(wildcard src/**/**/**/*.cpp)
OBJ  = $(SRC:.cpp=.o)
LDFLAGS = -g -lfftw3 -L/usr/local/lib
BIN = 1000th-summer
RELEASE = -static -static-libgcc -static-libstdc++

ifeq ($(r), 1)
	CFLAGS += $(RELEASE)
	LDFLAGS += $(RELEASE)
endif

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
	LDFLAGS += -lgdi32
endif

# ifeq ($(OSFLAG), WIN32)
# 	BIN = 1000th-summer.exe
# endif

CLEAN :=
ifeq ($(OSFLAG),WIN32)
	CLEAN = rm -rf 1000th-summer.exe $(OBJ) .fuse_ 1000th-summer.ilk 1000th-summer.pdb
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
	