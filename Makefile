CC=g++
CXXFLAGS=-ggdb -std=c++1z -Wall -O0 -fsanitize=leak,address,undefined,float-divide-by-zero -fno-omit-frame-pointer
LDFLAGS=-lasan -lubsan -lm -lSDL2

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: spn

spn: $(OBJECTS)
	$(CC) -o spn $(OBJECTS) $(LDFLAGS)

%.o: %.cpp %.hpp
	$(CC) -o $@ -c $< $(CXXFLAGS) 

run: spn
	SDL_VIDEODRIVER=wayland ./spn

clean:
	$(info Cleaning)
	rm -rf $(OBJECTS) spn
