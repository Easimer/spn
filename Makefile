CC=g++
CXXFLAGS=-g -std=c++17 -Wall
LDFLAGS=-lm

all: spn test

spn: spn.o geo.o vec.o light.o scene.o
	${CC} ${LDFLAGS} -o spn spn.o geo.o vec.o light.o scene.o

test: test.o geo.o vec.o
	${CC} ${LDFLAGS} -o test test.o geo.o vec.o

test.o: test.cpp
	${CC} ${CXXFLAGS} -o test.o -c test.cpp

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

tests: test
	./test

clean:
	rm -rf *.o spn test
