CC=g++
CXXFLAGS=-ggdb -std=c++1z -Wall -O0 -fsanitize=leak,address,undefined,float-divide-by-zero -fno-omit-frame-pointer -I include/
LDFLAGS=-lasan -lubsan -lm -lSDL2

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: spn

spn: $(OBJECTS) build
	$(CC) -o spn $(OBJECTS) $(LDFLAGS)

%.o: %.cpp include/%.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS) 

build:
	mkdir -p build

run: spn
	SDL_VIDEODRIVER=wayland ./spn

clean:
	$(info Cleaning)
	rm -rf $(OBJECTS) spn

