#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <cmath>

class Mandelbrot {
public:
	Mandelbrot();
	~Mandelbrot();

	static unsigned escape_time(const double, const double, const unsigned);
	static bool in_set(const double, const double, const unsigned);
	static double distance_estimator(const double, const double, const unsigned);
	static void color_escape_time(double *, const double, const double, const unsigned, const double, const double);
	static void color_distance_estimator(double * c, const double, const double, const unsigned, const double);

private:
	static double sq(const double);
	static double lerp(const double, const double, const double);
	static void color(double *, double);
	static void escape(double &, double &, unsigned &, const unsigned);
	
};

#endif