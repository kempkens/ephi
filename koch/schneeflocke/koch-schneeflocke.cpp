#include <cmath>
#include <cstdio>
#include "cairo.h"

double distance(double x1, double y1, double x2, double y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double sinArcTan(double x) {
	return x / sqrt(x * x + 1);
}

double cosArcTan(double x) {
	return 1.0 / sqrt(x * x + 1);
}

void zeichne(cairo_t *cr, double x1, double y1, double x2, double y2, int tiefe) {
	if (tiefe <= 0) {
		cairo_move_to(cr, x1, y1);
		cairo_line_to(cr, x2, y2);
		cairo_stroke(cr);
		return;
	}
	double xs, ys;
	if (y2 == y1) {
		if (x2 < x1) {
			xs = (x1 + x2) / 2;
			ys = (y1 + y2) / 2 + distance(x1, y1, x2, y2) * 
				sqrt(3) / 6;
		} else {
			xs = (x1 + x2) / 2;
			ys = (y1 + y2) / 2 - distance(x1, y1, x2, y2) * 
				sqrt(3) / 6;
		}
	} else if (y2 > y1) {
		xs = (x1 + x2) / 2 + distance(x1, y1, x2, y2) * 
			cosArcTan((x1 - x2) / (y2 - y1)) * sqrt(3) / 6;
		ys = (y1 + y2) / 2 + distance(x1, y1, x2, y2) * 
			sinArcTan((x1 - x2) / (y2 - y1)) * sqrt(3) / 6;
	} else {
		xs = (x1 + x2) / 2 - distance(x1, y1, x2, y2) * 
			cosArcTan((x1 - x2) / (y2 - y1)) * sqrt(3) / 6;
		ys = (y1 + y2) / 2 - distance(x1, y1, x2, y2) * 
			sinArcTan((x1 - x2) / (y2 - y1)) * sqrt(3) / 6;
	}
	// printf("(xs ; ys) = (%f ; %f)\n", xs, ys);
	zeichne(cr, x1, y1, (2 * x1 + x2) / 3, (2 * y1 + y2) / 3, tiefe - 1);
	zeichne(cr, (2 * x1 + x2) / 3, (2 * y1 + y2) / 3, xs, ys, tiefe - 1);
	zeichne(cr, xs, ys, (x1 + 2 * x2) / 3, (y1 + 2 * y2) / 3, tiefe - 1);
	zeichne(cr, (x1 + 2 * x2) / 3, (y1 + 2 * y2) / 3, x2, y2, tiefe - 1);
}

int main() {
	// Auflösung in Pixeln
	const double res = 1000;
	const double xsize = res;
	const double ysize = res;

	// Breite einer Linie in Pixeln
	const double line_width = 3;

	// maximale Anzahl Iterationen
	const unsigned maxTiefe = 8;

	cairo_surface_t *surface = cairo_image_surface_create (
    	CAIRO_FORMAT_ARGB32, xsize, ysize);
    cairo_t *cr = cairo_create (surface);

    cairo_set_line_width (cr, line_width / res);
    cairo_scale(cr, res, res);

	cairo_set_source_rgb (cr, 0, 0, 0);	

	zeichne(cr, .5 - sin(M_PI / 3) * .5, 0.5 + cos(M_PI / 3) * .5, .5, 0, maxTiefe);
	zeichne(cr, .5, 0, .5 + sin(M_PI / 3) * .5, 0.5 + cos(M_PI / 3) * .5, maxTiefe);
	zeichne(cr, .5 + sin(M_PI / 3) * .5, 0.5 + cos(M_PI / 3) * .5,
		.5 - sin(M_PI / 3) * .5, 0.5 + cos(M_PI / 3) * .5, maxTiefe);

	cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "koch-schneeflocke.png");
    cairo_surface_destroy (surface);
	
	return 0;
}
