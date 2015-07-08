#include <cmath>
#include <cstdio>
#include "cairo.h"

void triangle(cairo_t *cr, const double x1, const double y1, const double x2, const double y2, 
	double x3, double y3) {
	cairo_move_to(cr, x1, y1);
	cairo_line_to(cr, x2, y2);
	cairo_line_to(cr, x3, y3);
	cairo_line_to(cr, x1, y1);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);
}

void zeichne(cairo_t *cr, const double x1, const double y1, const double x2, const double y2, 
	const double x3, const double y3, const unsigned tiefe) {
	if (tiefe <= 0) {
		triangle(cr, x1, y1, x2, y2, x3, y3);
		return;
	}
	zeichne(cr, x1, y1, (x1 + x2) / 2, (y1 + y2) / 2, 
		(x1 + x3) / 2, (y1 + y3) / 2, tiefe - 1);
	zeichne(cr, (x1 + x2) / 2, (y1 + y2) / 2, x2, y2,
		(x2 + x3) / 2, (y2 + y3) / 2, tiefe - 1);
	zeichne(cr, (x1 + x3) / 2, (y1 + y3) / 2, 
		(x2 + x3) / 2, (y2 + y3) / 2, x3, y3, tiefe - 1);
}

int main() {
	// Auflösung in Pixeln
	const double res = 1000;
	const double xsize = res;
	const double ysize = sin(M_PI / 3) * res;

	// Breite einer Linie in Pixeln
	const double line_width = 3;

	// maximale Anzahl Iterationen
	const unsigned int iterations = 7;

	cairo_surface_t *surface = cairo_image_surface_create (
    	CAIRO_FORMAT_ARGB32, xsize, ysize);
    cairo_t *cr = cairo_create (surface);

    cairo_scale(cr, res, res);

    cairo_set_line_width (cr, line_width / res);
	cairo_set_source_rgb (cr, 0, 0, 0);

	const double space = 0.05;

	zeichne(cr, space, sin(M_PI / 3) - space, 1 - space,
		sin(M_PI / 3) - space, 0.5, space, iterations);

	cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "sierpinski.png");
    cairo_surface_destroy (surface);
		
	return 0;
}