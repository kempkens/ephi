#include "mandelbrot.h"

Mandelbrot::Mandelbrot() {

}

Mandelbrot::~Mandelbrot() {

}

double Mandelbrot::sq(const double a) {
    return a * a;
}

double Mandelbrot::lerp(const double a, const double b, const double t) {
    return (1.0 - t) * a + t * b;
}

void Mandelbrot::color(double * c, double r) {
    const double pos[6] = {0.0, 0.16, 0.42, 0.6425, 0.8575, 1.0};
    const unsigned char colors[6][3] =
        {
            {0, 7, 100},
            {32, 107, 203},
            {237, 255, 255},
            {255, 170, 0},
            {0, 2, 0},
            {0, 7, 100}
        };

    int p = 0;
    while (r > pos[p + 1]) {
        ++p;
    }
    for (int i = 0; i < 3; ++i) {
        c[i] = lerp((double)colors[p][i] / 255.0, (double)colors[p + 1][i] / 255.0, 
            (r - pos[p]) / (pos[p + 1] - pos[p]));
    }
}

void Mandelbrot::escape(double &x0, double &y0, unsigned &iteration, const unsigned max_iteration) {
    double t = x0 - 0.25;
    double q = sq(t) + sq(y0);
    // Quasi-Kreise erkennen
    if (q * (q + t) < 0.25 * sq(y0) || sq(x0 + 1) + sq(y0) < 0.0625) {
        iteration = max_iteration;
        return;
    }
    double x = 0; // Re z
    double y = 0; // Im z
    double xsq = 0; // (Re z)^2
    double ysq = 0; // (Im z)^2
    iteration = 0;
    while (xsq + ysq < 10 && iteration < max_iteration) {
        // z = z^2 + c
        y = x * y;
        y += y;
        y += y0;
        x = xsq - ysq + x0;
        xsq = sq(x);
        ysq = sq(y);
        ++iteration;
    }
    x0 = x;
    y0 = y;
}

unsigned Mandelbrot::escape_time(const double x0, const double y0, const unsigned max_iteration) {
    double x = x0;
    double y = y0;
    unsigned iteration;
    escape(x, y, iteration, max_iteration);
    return iteration;
}

bool Mandelbrot::in_set(const double x0, const double y0, const unsigned max_iteration) {
    return escape_time(x0, y0, max_iteration) == max_iteration;
}

double Mandelbrot::distance_estimator(const double x0, const double y0, const unsigned max_iteration) {
    double x = 0; // Re z
    double y = 0; // Im z
    double xsq = 0; // (Re z)^2
    double ysq = 0; // (Im z)^2
    double dzx = 0; // Re dz
    double dzy = 0; // Im dz
    unsigned iteration = 0;
    while (xsq + ysq <= 1E20 && iteration < max_iteration) {
        double t = dzx;
        // dz = 2 * dz * z + 1
        dzx = 2.0 * (x * dzx - y * dzy) + 1;
        dzy = 2.0 * (x * dzy + y * t);
        // z = z^2 + c
        y = 2.0 * x * y + y0;
        x = xsq - ysq + x0;
        xsq = sq(x);
        ysq = sq(y);
        ++iteration;
    }
    double b = sqrt(xsq + ysq) * log(xsq + ysq) / sqrt(dzx * dzx + dzy * dzy);
    return b;
}

void Mandelbrot::color_escape_time(double * c, const double x0, const double y0, const unsigned max_iteration, 
    const double scale, const double shift) {

    const double ONE_OVER_LOG2 = 1.0 / log(2);

    double x = x0;
    double y = y0;
    unsigned iteration;
    escape(x, y, iteration, max_iteration);

    if (iteration == max_iteration) {
        c[0] = 0;
        c[1] = 0;
        c[2] = 0;
        c[3] = 1;
        return;
    }
    double size = sqrt(x * x + y * y);
    double smoothed = log(log(size) * ONE_OVER_LOG2) * ONE_OVER_LOG2;
    double r = (((double)iteration + 1 - smoothed) * scale + shift) / (double)max_iteration;
    color(c, r);
}

void Mandelbrot::color_distance_estimator(double * c, const double x0, const double y0, const unsigned max_iteration,
    const double k) {

    double b = distance_estimator(x0, y0, max_iteration);
    if (b < 0) {
        c[0] = 0;
        c[1] = 0;
        c[2] = 0;
        c[3] = 1;
        return;
    }
    double r = 0 - k * log(b);
    color(c, r);
}