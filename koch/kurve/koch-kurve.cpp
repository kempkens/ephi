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

	// Breite einer Linie in Pixeln
	const double line_width = 3;

	const double d = sin(M_PI / 3.0) / 3.0;
	const double space = .05;
	const double xsize = res * 1;
	const double ysize = res * (4 * d + 8 * space);

	cairo_surface_t *surface = cairo_image_surface_create (
    	CAIRO_FORMAT_ARGB32, xsize, ysize);
    cairo_t *cr = cairo_create (surface);

    cairo_set_line_width (cr, line_width / res);
    cairo_scale(cr, res, res);

	cairo_set_source_rgb (cr, 0, 0, 0);	
	
	for (int i = 0; i < 4; ++i) {
		zeichne(cr, 0, i * d + (i+1) * space, 
			1, i * d + (i+1) * space, i);
	}

	zeichne(cr, 0, 4 * d + 7 * space, 
			1, 4 * d + 7 * space, 6);

	cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "koch-kurve.png");
    cairo_surface_destroy (surface);
		
	return 0;
}