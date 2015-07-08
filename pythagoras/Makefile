CXX=g++
LD=g++
RM=rm -f
CPPFLAGS=-g -Wall `pkg-config --cflags cairo`
LDFLAGS=-g
LDLIBS=-g `pkg-config --libs cairo`

all: pythagoras

pythagoras: pythagoras.o
	$(LD) $(LDFLAGS) -o pythagoras pythagoras.o $(LDLIBS)

pythagoras.o: pythagoras.cpp
	$(CXX) $(CPPFLAGS) -c pythagoras.cpp

clean:
	$(RM) *.o

dist-clean:
	$(RM) *.o pythagoras