#ifndef DLA_H
#define DLA_H

#include <cmath>
#include <vector>

#include "random.h"

namespace dla {

	struct Point {
		int x;
		int y;
	};

	Point make_point(int x, int y) {
		Point p;
		p.x = x;
		p.y = y;
		return p;
	}

	double abs(Point p, const int center) {
		return sqrt((p.x - center) * (p.x - center) + 
			(p.y - center) * (p.y - center));
	}

	double max(double a, double b) {
		return (a > b) ? a : b;
	}

	double min(double a, double b) {
		return (a < b) ? a : b;
	}

	bool is_set(bool *s, const int x, const int y, const int size) {
		if (x >= 0 && x < size && y >= 0 && y < size) {
			return s[x * size + y];
		} else {
			return false;
		}
	}	

	bool is_adjacent(bool *s, Point p, const int size) {
		if (is_set(s, p.x, p.y - 1, size)) {
			return true;
		}
		if (is_set(s, p.x - 1, p.y, size)) {
			return true;
		}
		if (is_set(s, p.x + 1, p.y, size)) {
			return true;
		}
		if (is_set(s, p.x, p.y + 1, size)) {
			return true;
		}
		return false;
	}

	Point random_point_on_circle(int cx, int cy, double r) {
		double phi = (double)(fastrandom::xorshf96() % 1024) / 1024.0 * 2 * M_PI;
		int x = round(cx + cos(phi) * r);
		int y = round(cy + sin(phi) * r);
		Point p = make_point(x, y);
		return p;
	}

	void calculate_radii(const double radius, double &initial_radius, double &jump_radius, double &kill_radius) {
		initial_radius = 1.1 * (radius + 5.0);
		jump_radius = 1.1 * (radius + 5.0);
		kill_radius = 1.3 * (radius + 5.0);
	}

	Point move_random(Point p, const int center, const double radius, const double initial_radius, 
		const double jump_radius, const double kill_radius) {

		int d = fastrandom::xorshf96() % 4;
		switch (d) {
			case 0: ++p.x; break;
			case 1: --p.x; break;
			case 2: ++p.y; break;
			case 3: --p.y; break;
		}

		double r = abs(p, center);
		while (r > jump_radius) {
			if (r > kill_radius) {
				p = random_point_on_circle(center, center, 
					initial_radius);
			} else {
				p = random_point_on_circle(p.x, p.y, r - radius);
			}
			r = abs(p, center);
		}

		return p;
	}
}

#endif