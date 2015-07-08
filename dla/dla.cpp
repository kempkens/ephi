#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "cairo.h"
#include "dla.h"

int main(int argc, char * argv[]) {

	// Größe in Pixeln
	const int size = 1000;
	const int center = size / 2;

	// Anzahl Partikel
	const int particles = 32000;

	// s hat Größe size x size
	bool s[size * size] = {false};

	cairo_surface_t *surface = cairo_image_surface_create (
    	CAIRO_FORMAT_ARGB32, size, size);
    cairo_t *cr = cairo_create (surface);

	cairo_set_source_rgb (cr, 0, 0, 0);

    s[center * size + center] = true;
    cairo_rectangle(cr, center, center, 1, 1);
    cairo_fill(cr);

    double radius = 0;
    double initial_radius, jump_radius, kill_radius;
    dla::calculate_radii(radius, initial_radius, jump_radius, kill_radius);

    for (int i = 0; i < particles; ++i) {
    	dla::Point p = dla::random_point_on_circle(center, center, 
    		initial_radius);
    	
    	bool move = true;
    	while (move) {
    		if (dla::is_adjacent(s, p, size)) {
    			s[p.x * size + p.y] = true;
    			double r = dla::abs(p, center);
    			if (radius < r) {
    				radius = r;
    				dla::calculate_radii(radius, initial_radius, jump_radius, kill_radius);
    			}
    			cairo_rectangle(cr, p.x, p.y, 1, 1);
    			cairo_fill(cr);
    			move = false;
    		}
    		if (move) {
    			p = dla::move_random(p, center, radius, initial_radius, jump_radius, kill_radius);
    		}
    	}
    }

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "dla.png");
    cairo_surface_destroy (surface);
    return 0;
}