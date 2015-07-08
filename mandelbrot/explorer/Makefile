CXX=g++
LD=g++
RM=rm -f
CPPFLAGS=-Wall -g -std=c++11
LDFLAGS=-g
LDLIBS=-L/usr/lib/i386-linux-gnu -lSDL2 -lGL -lGLU

all: mandelbrot-explorer

mandelbrot-explorer: main.o gui.o mandelbrot.o
	$(LD) $(LDFLAGS) -o mandelbrot-explorer main.o gui.o mandelbrot.o $(LDLIBS)

main.o: main.cpp gui.h
	$(CXX) $(CPPFLAGS) -c main.cpp

gui.o: gui.cpp gui.h mandelbrot.h
	$(CXX) $(CPPFLAGS) -c gui.cpp

mandelbrot.o: mandelbrot.cpp mandelbrot.h
	$(CXX) $(CPPFLAGS) -c mandelbrot.cpp

clean:
	$(RM) *.o

dist-clean:
	$(RM) *.o mandelbrot-explorer