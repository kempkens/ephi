#include "gui.h"

GUI::GUI() {

}

GUI::~GUI() {

}

int GUI::init() {
	// SDL initialisieren
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "Fehler beim Initialisieren von SDL: %s\n", SDL_GetError());
        return 1;
    }

	// OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Fenster erstellen
	if ((window = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		window_width, window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)) == NULL) {
		fprintf(stderr, "Fehler beim Erstellen des Fensters: %s\n", SDL_GetError());
		return 1;
	}

	// OpenGL context erstellen
	if ((context = SDL_GL_CreateContext(window)) == NULL) {
		fprintf(stderr, "Fehler: %s\n", SDL_GetError());
		return 1;
	}

	// Vsync
	if (SDL_GL_SetSwapInterval(1) != 0) {
		fprintf(stderr, "Warnung: Vsync konnte nicht aktiviert werden.\n");
	}

	// OpenGL initialisieren
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, window_width, 0, window_height, -1, 1);

	return 0;
}

void GUI::cleanup() {
	// aufräumen
	SDL_Quit();
}

int GUI::run() {
	if (init() != 0) {
		return 1;
	}

	clear_screen();

	SDL_Event event;

	while (running) {
		SDL_WaitEvent(&event);
        while(SDL_PollEvent(&event)) {
            handle_event(&event);
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        user_input(state);

        // Bild soll neu gerendert werden
        if (change) {
        	render();
        }
	}
	
	cleanup();

	return 0;
}

void GUI::clear_screen() {
	// gesamtes Fenster weiß füllen
	glClear(GL_COLOR_BUFFER_BIT);
}

void GUI::render() {
	const double xmin = xm - 0.5 * d;
	const double ymin = ym - 0.5 * d * (double)window_height / (double)window_width;

	const double res = (double)window_width / d;

	glBegin(GL_POINTS);
	double rgba[4] = {0, 0, 0, 0};
	double scale = 1;
	double shift = 0;
	for (unsigned px = 0; px < window_width; ++px) {
		for (unsigned py = 0; py < window_height; ++py) {
			double x = (double)px / res + xmin;
			double y = (double)py / res + ymin;
			Mandelbrot::color_escape_time(&rgba[0], x, y, max_iteration, scale, shift);
			glColor4dv(&rgba[0]);
			glVertex2f(px, py);
		}
	}
	glEnd();
	SDL_GL_SwapWindow(window);

	change = false;
}

void GUI::handle_event(SDL_Event *event) {
	// Programm beenden
	if (event->type == SDL_QUIT) {
		running = false;
	}
}

void GUI::user_input(const Uint8 *state) {
	// Programm beenden
	if (state[SDL_SCANCODE_ESCAPE]) {
		running = false;
	}

	// Verschieben
	if (state[SDL_SCANCODE_W]) {
		ym += 0.1 * d;
		change = true;
	}
	if (state[SDL_SCANCODE_A]) {
		xm -= 0.1 * d;
		change = true;
	}
	if (state[SDL_SCANCODE_S]) {
		ym -= 0.1 * d;
		change = true;
	}
	if (state[SDL_SCANCODE_D]) {
		xm += 0.1 * d;
		change = true;
	}


	// Zoom
	if (state[SDL_SCANCODE_X]) {
		d /= 2;
		change = true;
	}
	if (state[SDL_SCANCODE_Z]) {
		d *= 2;
		change = true;
	}
}