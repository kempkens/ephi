CXX=g++
LD=g++
RM=rm -f
CPPFLAGS=-g -Wall `pkg-config --cflags cairo`
LDFLAGS=-g
LDLIBS=-g `pkg-config --libs cairo`

all: mandelbrot

mandelbrot: mandelbrot.o
	$(LD) $(LDFLAGS) -o mandelbrot mandelbrot.o $(LDLIBS)

mandelbrot.o: mandelbrot.cpp mandelbrot.h
	$(CXX) $(CPPFLAGS) -c mandelbrot.cpp

clean:
	$(RM) *.o

dist-clean:
	$(RM) *.o mandelbrot