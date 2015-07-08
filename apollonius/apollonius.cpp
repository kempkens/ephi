#include <cstdio>
#include <cmath>
#include "apollonius.h"
#include "cairo.h"

void drawCircle(cairo_t *cr, const apollonius::Circle k, const unsigned it) {
	cairo_arc(cr, k.center.x, k.center.y, k.r, 0, 2.0 * M_PI);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_stroke(cr);
}

// neue Kreise berühren nicht den äußeren Kreis
void recursiveInner(cairo_t * cr, 
	const apollonius::Circle k1, const apollonius::Circle k2, const apollonius::Circle k3, 
	const unsigned it, const double scaling, const double treshold) {

	if (it == 0) {
		return;
	}
	apollonius::Circle inner = apollonius::innerSoddy(k1, k2, k3);
	if (inner.r * scaling < treshold) {
		return;
	}
	drawCircle(cr, inner, it);
	recursiveInner(cr, k1, k2, inner, it - 1, scaling, treshold);
	recursiveInner(cr, k1, k3, inner, it - 1, scaling, treshold);
	recursiveInner(cr, k2, k3, inner, it - 1, scaling, treshold);
}

// neue Kreise berühren den äußeren Kreis
void recursiveBorder(cairo_t * cr, 
	const apollonius::Circle k1, const apollonius::Circle k2, const apollonius::Circle outer, 
	const unsigned it, const double scaling, const double treshold) {

	if (it == 0) {
		return;
	}
	apollonius::Circle k3 = tangentSoddy(k1, k2, outer);
	if (k3.r * scaling < treshold) {
		return;
	}
	drawCircle(cr, k3, it);
	recursiveInner(cr, k1, k2, k3, it - 1, scaling, treshold);
	recursiveBorder(cr, k1, k3, outer, it - 1, scaling, treshold);
	recursiveBorder(cr, k2, k3, outer, it - 1, scaling, treshold);
}

int main() {
	// Auflösung in Pixeln
	const double res = 1000;
	const double xsize = res;
	const double ysize = res;

	// Breite einer Linie in Pixeln
	const double line_width = 3;

	// maximale Anzahl Iterationen
	const unsigned int iterations = 50;

	// kleinster Radius (Abbruchbedingung)
	const double treshold = 0.2;

	// Radii der drei Ausgangskreise
	const double r1 = 1;
	const double r2 = 1;
	const double r3 = 1;

	apollonius::Circle k1, k2, k3, outer;
	k1 = apollonius::makeCircle(0, 0, r1);
	k2 = apollonius::makeCircle(r1 + r2, 0, r2);
	double alpha = acos(((r1 + r2) * (r1 + r2) + (r1 + r3) * (r1 + r3) - (r2 + r3) * (r2 + r3)) 
		/ (2.0 * (r1 + r2) * (r1 + r3)));
	printf("alpha = %.2f°\n", alpha * 180.0 / M_PI);
	k3 = apollonius::makeCircle(cos(alpha) * (r1 + r3), -sin(alpha) * (r1 + r3), r3);
	outer = apollonius::outerSoddy(k1, k2, k3);

	printf("1st circle: center(%.2f;%.2f), radius = %.2f\n", k1.center.x, k1.center.y, k1.r);
	printf("2nd circle: center(%.2f;%.2f), radius = %.2f\n", k2.center.x, k2.center.y, k2.r);
	printf("3rd circle: center(%.2f;%.2f), radius = %.2f\n", k3.center.x, k3.center.y, k3.r);
	printf("outer circle: center(%.2f;%.2f), radius = %.2f\n", outer.center.x, outer.center.y, outer.r);

	cairo_surface_t *surface = cairo_image_surface_create (
    	CAIRO_FORMAT_ARGB32, xsize, ysize);
    cairo_t *cr = cairo_create (surface);

    // kleinen Rand lassen, deshalb mit 0.495 statt 0.5 skalieren
    double scaling = 0.495 * res / outer.r;
	cairo_scale(cr, scaling, scaling);
	cairo_translate(cr, outer.r - outer.center.x + 0.025, outer.r - outer.center.y + 0.025);

	cairo_set_line_width (cr, line_width / scaling);

	// alle drei Ausgangskreise sowie äußeren Soddy-Kreis zeichnen
	drawCircle(cr, outer, 0);
	drawCircle(cr, k1, iterations + 1);
	drawCircle(cr, k2, iterations + 1);
	drawCircle(cr, k3, iterations + 1);

	recursiveInner(cr, k1, k2, k3, iterations, scaling, treshold);
	recursiveBorder(cr, k1, k2, outer, iterations, scaling, treshold);
	recursiveBorder(cr, k1, k3, outer, iterations, scaling, treshold);
	recursiveBorder(cr, k2, k3, outer, iterations, scaling, treshold);

	cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "apollonius.png");
    cairo_surface_destroy (surface);

	return 0;
}