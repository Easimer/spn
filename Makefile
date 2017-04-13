CC=g++
#CXXFLAGS=-O2 -mtune=native -march=native -std=c++1z -Wall
CXXFLAGS=-ggdb -std=c++1z -Wall -O0 -fsanitize=leak,address -fno-omit-frame-pointer
LDFLAGS=-lasan -lm -lSDL2

all: spn

spn: spn.o geo.o vec.o light.o scene.o renderer.o
	$(info Linking spn)
	${CC} -o spn spn.o geo.o vec.o light.o scene.o renderer.o ${LDFLAGS}

spn.o: spn.cpp
	${CC} ${CXXFLAGS} -o spn.o -c spn.cpp

geo.o: geo.cpp geo.hpp
	${CC} ${CXXFLAGS} -o geo.o -c geo.cpp

vec.o: vec.cpp vec.hpp
	${CC} ${CXXFLAGS} -o vec.o -c vec.cpp

scene.o: scene.cpp scene.hpp
	${CC} ${CXXFLAGS} -o scene.o -c scene.cpp

light.o: light.cpp light.hpp
	${CC} ${CXXFLAGS} -o light.o -c light.cpp

renderer.o: renderer.cpp renderer.hpp
	${CC} ${CXXFLAGS} -o renderer.o -c renderer.cpp

clean:
	$(info Cleaning)
	rm -rf *.o spn test
