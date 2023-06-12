CC = clang++
CFLAGS = -g
SRC  = $(wildcard src/**/*.cpp) $(wildcard src/*.cpp) $(wildcard src/**/**/*.cpp) $(wildcard src/**/**/**/*.cpp)
OBJ  = $(SRC:.cpp=.o)
LDFLAGS = -g

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

CLEAN :=
ifeq ($(OSFLAG),WIN32)
	CLEAN = del /q /s 1000th-summer.exe *.o .fuse_
else
	CLEAN = rm -rf 1000th-summer $(OBJ) .fuse_ frags
endif

all: 1000th-summer

1000th-summer: $(OBJ)
	$(CC) -o 1000th-summer $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

test:
	echo $(SRC)
	echo $(OBJ)

clean:
	$(CLEAN)

os:
	echo $(OSFLAG)