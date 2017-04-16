CC=g++
CXXFLAGS=-ggdb -std=c++1z -Wall -O0 -fsanitize=leak,address,undefined,float-divide-by-zero -fno-omit-frame-pointer -fPIC -I include/
LDFLAGS=-lasan -lubsan -ldl -lm -lSDL2 -lSDL2_image -llua

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: spn

spn: $(OBJECTS)
	LIBRARY_PATH=../lua-prefix/lib/ $(CC) -o spn $(OBJECTS) $(LDFLAGS)

src/%.o: src/%.cpp include/%.hpp
	$(CC) $(CXXFLAGS) -o $@ -c $<

run: spn
	SDL_VIDEODRIVER=wayland ./spn test.scn

runx: spn
	./spn test.scn

clean:
	$(info Cleaning)
	rm -rf $(OBJECTS) spn

