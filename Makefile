CC = g++
CFLAGS = -g
SRC  = $(wildcard src/**/*.cpp) $(wildcard src/*.cpp) $(wildcard src/**/**/*.cpp) $(wildcard src/**/**/**/*.cpp)
OBJ  = $(SRC:.cpp=.o)
LDFLAGS = -g

all: 1000th-summer

1000th-summer: $(OBJ)
	$(CC) -o 1000th-summer $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

test:
	echo $(SRC)
	echo $(OBJ)

clean:
	rm -rf 1000th-summer $(OBJ) .fuse_
