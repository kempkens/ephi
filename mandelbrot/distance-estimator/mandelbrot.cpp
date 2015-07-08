#include <cstdio>
#include <cstdlib>
#include "cairo.h"
#include "mandelbrot.h"

int main(int argc, char * argv[]) {
    if (argc != 6) {
        printf("Gebrauch: %s [xm] [ym] [d] [max_iteration] [k]\n", argv[0]);
        return 1;
    }
    
    const double xm = atof(argv[1]);
    const double ym = atof(argv[2]);
    const double d = atof(argv[3]);
    const int max_iteration = atoi(argv[4]);
    const double k = atof(argv[5]);

    printf("Zentrumskoordianten: %.6f + %.6fi\n", xm, ym);
    printf("Horizontaler Bilddurchmesser: %.6f\n", d);
    printf("Vergrößerung relativ zum Startbild: %.1f\n", 3.0769 / d);
    printf("Testzyklen: %d\n", max_iteration);
    printf("Farbverlauf: um %.3f skaliert\n", k);

    const double xmin = xm - d / 2.0;
    const double ymin = -ym - d / 2.0 * 3.0 / 4.0;

    const int xsize = 1024;
    const int ysize = 768;

    const double res = (double)xsize / d;

    cairo_surface_t *surface = cairo_image_surface_create (
        CAIRO_FORMAT_ARGB32, xsize, ysize);
    cairo_t *cr = cairo_create (surface);

    cairo_set_line_width (cr, 1);


    for (int Px = 0; Px < xsize; ++Px) {
        for (int Py = 0; Py < ysize; ++Py) {
            double x0 = (double)Px / res + xmin;
            double y0 = (double)Py / res + ymin;
            double rgba[4] = {0, 0, 0, 1};
            mandelbrot::color_distance_estimator(&rgba[0], x0, y0, max_iteration, k);
            cairo_set_source_rgb(cr, rgba[0], rgba[1], rgba[2]);
            cairo_rectangle(cr, Px, Py, 1, 1);
            cairo_fill(cr);
        }
    }

    cairo_destroy (cr);
    cairo_surface_write_to_png (surface, "mandelbrot.png");
    cairo_surface_destroy (surface);
    return 0;
}