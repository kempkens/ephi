#ifndef GUI_H
#define GUI_H

#include "SDL2/SDL.h"
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <string>
#include "mandelbrot.h"

class GUI {
public:
	GUI();
	~GUI();

	int run();

private:
	int init();
	void cleanup();
	void render();
	void clear_screen();
	void handle_event(SDL_Event *);
	void user_input(const Uint8 *);

	SDL_Window *window = NULL;
	SDL_GLContext context = NULL;
	std::string window_title = "Mandelbrot-Menge";
	const unsigned window_width = 640;
	const unsigned window_height = 480;

	bool running = true;
	bool change = true;

	double xm = -0.7;
	double ym = 0;
	double d = 4;
	unsigned max_iteration = 50;
};

#endif