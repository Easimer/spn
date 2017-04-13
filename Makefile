CC=g++
CXXFLAGS=-ggdb -std=c++1z -Wall -O0 -fsanitize=leak,address,undefined,float-divide-by-zero -fno-omit-frame-pointer -I include/
LDFLAGS=-lasan -lubsan -lm -lSDL2

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: spn

spn: $(OBJECTS)
	$(CC) -o spn $(OBJECTS) $(LDFLAGS)

src/%.o: src/%.cpp include/%.hpp
	$(CC) $(CXXFLAGS) -o $@ -c $<

run: spn
	SDL_VIDEODRIVER=wayland ./spn test.scn

clean:
	$(info Cleaning)
	rm -rf $(OBJECTS) spn

