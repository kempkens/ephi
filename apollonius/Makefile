CXX=g++
LD=g++
RM=rm -f
CPPFLAGS=-g -Wall `pkg-config --cflags cairo`
LDFLAGS=-g
LDLIBS=-g `pkg-config --libs cairo`

all: apollonius

apollonius: apollonius.o
	$(LD) $(LDFLAGS) -o apollonius apollonius.o $(LDLIBS)

apollonius.o: apollonius.cpp apollonius.h
	$(CXX) $(CPPFLAGS) -c apollonius.cpp

clean:
	$(RM) *.o

dist-clean:
	$(RM) *.o apollonius