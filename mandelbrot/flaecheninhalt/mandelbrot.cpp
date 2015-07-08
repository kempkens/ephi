#include <cstdio>
#include "mandelbrot.h"

int main(int argc, char * argv[]) {
    const double xm = -0.7;
    const double ym = 0;
    const double d = 3.0769;
    const int max_iteration = 8000;

    const int xsize = 4000;
    const int ysize = 3000;

    const double res = (double)xsize / d;

    const double xmin = xm - d / 2.0;
    const double ymin = -ym - d / 2.0 * ysize / xsize;

    long long count = 0;
    for (int Px = 0; Px < xsize; ++Px) {
        for (int Py = 0; Py < ysize; ++Py) {
            double x0 = (double)Px / res + xmin;
            double y0 = (double)Py / res + ymin;

            unsigned iteration = mandelbrot::escape_time(x0, y0, max_iteration);
            if (iteration == max_iteration) {
                ++count;
            }
        }
    }

    double area = (double)count * mandelbrot::sq(d) / mandelbrot::sq(xsize);

    printf("area = %.6f\n", area);

    return 0;
}