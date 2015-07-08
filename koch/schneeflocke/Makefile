CXX=g++
LD=g++
RM=rm -f
CPPFLAGS=-g -Wall `pkg-config --cflags cairo`
LDFLAGS=-g
LDLIBS=-g `pkg-config --libs cairo`

all: koch-schneeflocke

koch-schneeflocke: koch-schneeflocke.o
	$(LD) $(LDFLAGS) -o koch-schneeflocke koch-schneeflocke.o $(LDLIBS)

koch-schneeflocke.o: koch-schneeflocke.cpp
	$(CXX) $(CPPFLAGS) -c koch-schneeflocke.cpp

clean:
	$(RM) *.o

dist-clean:
	$(RM) *.o koch-schneeflocke