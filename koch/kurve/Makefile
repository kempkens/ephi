CXX=g++
LD=g++
RM=rm -f
CPPFLAGS=-g -Wall `pkg-config --cflags cairo`
LDFLAGS=-g
LDLIBS=-g `pkg-config --libs cairo`

all: koch-kurve

koch-kurve: koch-kurve.o
	$(LD) $(LDFLAGS) -o koch-kurve koch-kurve.o $(LDLIBS)

koch-kurve.o: koch-kurve.cpp
	$(CXX) $(CPPFLAGS) -c koch-kurve.cpp

clean:
	$(RM) *.o

dist-clean:
	$(RM) *.o koch-kurve