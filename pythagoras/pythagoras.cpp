#include <cmath>
#include <cstdio>
#include "cairo.h"

double distance(const double x1, const double y1, const double x2, const double y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double sinArcTan(const double x) {
	return x / sqrt(x * x + 1);
}

double cosArcTan(const double x) {
	return 1.0 / sqrt(x * x + 1);
}

void quadrat(cairo_t *cr, const double x1, const double y1, const double x2, const double y2) {
	cairo_move_to(cr, x1, y1);
	cairo_line_to(cr, x2, y2);
	cairo_line_to(cr, x2 + y2 - y1, y2 - x2 + x1);
	cairo_line_to(cr, x1 + y2 - y1, y1 - x2 + x1);
	cairo_line_to(cr, x1, y1);
	cairo_fill(cr);
}

void zeichne(cairo_t *cr, const double x1, const double y1, const double x2, const double y2, 
	const double a, const double b, const double c, unsigned iterationen) {

	if (iterationen <= 0) {
		return;
	}
	
	double r = distance(x1, y1, x2, y2) / c;
	double p = r * a * a / c;
	double h = r * a * b / c;
	double m = - (y2 - y1) / (x2 - x1);

	double x3, y3;
	if (x1 < x2) {
		x3 = x1 + p * cosArcTan(m) - h * sinArcTan(m);
		y3 = y1 - p * sinArcTan(m) - h * cosArcTan(m);
	} else {
		x3 = x1 - p * cosArcTan(m) + h * sinArcTan(m);
		y3 = y1 + p * sinArcTan(m) + h * cosArcTan(m);
	}

	quadrat(cr, x1, y1, x3, y3);
	zeichne(cr, x1 + y3 - y1, y1 - x3 + x1, x3 + y3 - y1, y3 - x3 + x1, a, b, c, iterationen - 1);
	quadrat(cr, x3, y3, x2, y2);
	zeichne(cr, x3 + y2 - y3, y3 - x2 + x3, x2 + y2 - y3, y2 - x2 + x3, a, b, c, iterationen - 1);
}

int main() {
	// Auflösung in Pixeln
	const double res = 1000;
	const double xsize = res;
	const double ysize = 3.0 / 4.0 * res;

	// Breite einer Linie in Pixeln
	const double line_width = 3;

	// Anzahl Iterationen
	const unsigned int iterationen = 10;

	// Seitenlängen der Ausgangsquadrate (c^2 == a^2 + b^2)
	const double prescale = 0.03;
	const double a = 3 * prescale;
	const double b = 4 * prescale;
	const double c = 5 * prescale;

	cairo_surface_t *surface = cairo_image_surface_create (
    	CAIRO_FORMAT_ARGB32, xsize, ysize);
    cairo_t *cr = cairo_create (surface);

    cairo_set_line_width (cr, line_width / res);
	cairo_set_source_rgb (cr, 0, 0, 0);

	cairo_scale(cr, res, res);

	quadrat(cr, .35, .7, .35 + c, .7);
	zeichne(cr, .35, .7 - c, .35 + c, .7 - c, a, b, c, iterationen);

	cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "pythagoras.png");
    cairo_surface_destroy (surface);

	return 0;
}