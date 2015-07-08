CXX=g++
LD=g++
RM=rm -f
CPPFLAGS=-g -Wall `pkg-config --cflags cairo`
LDFLAGS=-g
LDLIBS=-g `pkg-config --libs cairo`

all: sierpinski

sierpinski: sierpinski.o
	$(LD) $(LDFLAGS) -o sierpinski sierpinski.o $(LDLIBS)

sierpinski.o: sierpinski.cpp
	$(CXX) $(CPPFLAGS) -c sierpinski.cpp

clean:
	$(RM) *.o

dist-clean:
	$(RM) *.o sierpinski