CXX=g++
LD=g++
RM=rm -f
CPPFLAGS=-g -Wall `pkg-config --cflags cairo`
LDFLAGS=-g
LDLIBS=-g `pkg-config --libs cairo`

all: dla

dla: dla.o
	$(LD) $(LDFLAGS) -o dla dla.o $(LDLIBS)

dla.o: dla.cpp dla.h random.h
	$(CXX) $(CPPFLAGS) -c dla.cpp

clean:
	$(RM) *.o

dist-clean:
	$(RM) *.o dla