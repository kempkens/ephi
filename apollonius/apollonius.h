#ifndef APOLLONIUS_H
#define APOLLONIUS_H

#include <cmath>

namespace apollonius {

	struct Point {
		double x;
		double y;
	};

	struct Circle {
		Point center;
		double r;
	};

	Circle makeCircle(const double x, const double y, const double r) {
		Circle k;
		k.center.x = x;
		k.center.y = y;
		k.r = r;
		return k;
	}

	Point makePoint(const double x, const double y) {
		Point p;
		p.x = x;
		p.y = y;
		return p;
	}

	double circumradius(const double a, const double b, const double c) {
		return a * b * c / sqrt((a + b + c) * (b + c - a) * (c + a - b) * (a + b - c));
	}

	double abs(const Point p) {
		return sqrt(p.x * p.x + p.y * p.y);
	}

	Point sub(const Point p1, const Point p2) {
		return makePoint(p1.x - p2.x, p1.y - p2.y);
	}

	Point add(const Point p1, const Point p2) {
		return makePoint(p1.x + p2.x, p1.y + p2.y);
	}

	Point mul(const Point p, const double r) {
		return makePoint(p.x * r, p.y * r);
	}

	Circle innerSoddy(const Circle k1, const Circle k2, const Circle k3) {
		const double a = abs(sub(k2.center, k3.center));
		const double b = abs(sub(k1.center, k3.center));
		const double c = abs(sub(k1.center, k2.center));
		const double r = circumradius(a, b, c);
		const double fa = 1.0 + b * c / (2.0 * (-a + b + c) * r);
		const double fb = 1.0 + c * a / (2.0 * (-b + c + a) * r);
		const double fc = 1.0 + a * b / (2.0 * (-c + a + b) * r);
		Point center;
		center = mul(k1.center, a * fa);
		center = add(center, mul(k2.center, b * fb));
		center = add(center, mul(k3.center, c * fc));
		center = mul(center, 1.0 / (a * fa + b * fb + c * fc));
		Circle inner;
		inner.center = center;
		inner.r = k1.r * k2.r * k3.r / (k1.r * k2.r + k1.r * k3.r + k2.r * k3.r + 2.0 * sqrt(k1.r * k2.r * k3.r * (k1.r + k2.r + k3.r)));
		return inner;
	}

	Circle outerSoddy(const Circle k1, const Circle k2, const Circle k3) {
		const double a = abs(sub(k2.center, k3.center));
		const double b = abs(sub(k1.center, k3.center));
		const double c = abs(sub(k1.center, k2.center));
		const double r = circumradius(a, b, c);
		const double fa = -1.0 + b * c / (2.0 * (-a + b + c) * r);
		const double fb = -1.0 + c * a / (2.0 * (-b + c + a) * r);
		const double fc = -1.0 + a * b / (2.0 * (-c + a + b) * r);
		Point center;
		center = mul(k1.center, a * fa);
		center = add(center, mul(k2.center, b * fb));
		center = add(center, mul(k3.center, c * fc));
		center = mul(center, 1.0 / (a * fa + b * fb + c * fc));
		Circle outer;
		outer.center = center;
		outer.r = - k1.r * k2.r * k3.r / (k1.r * k2.r + k1.r * k3.r + k2.r * k3.r - 2.0 * sqrt(k1.r * k2.r * k3.r * (k1.r + k2.r + k3.r)));
		return outer;
	}

	Circle tangentSoddy(const Circle k1, const Circle k2, const Circle outer) {
		const double a = abs(sub(k2.center, outer.center));
		const double b = abs(sub(k1.center, outer.center));
		const double c = -abs(sub(k1.center, k2.center));
		const double r = circumradius(a, b, c);
		const double fa = -1.0 + b * c / (2.0 * (-a + b + c) * r);
		const double fb = -1.0 + c * a / (2.0 * (-b + c + a) * r);
		const double fc = -1.0 + a * b / (2.0 * (-c + a + b) * r);
		Point center;
		center = mul(k1.center, a * fa);
		center = add(center, mul(k2.center, b * fb));
		center = add(center, mul(outer.center, c * fc));
		center = mul(center, 1.0 / (a * fa + b * fb + c * fc));
		Circle k3;
		k3.center = center;
		k3.r = - k1.r * k2.r * outer.r / (k1.r * k2.r - k1.r * outer.r - k2.r * outer.r - 2.0 * sqrt(- k1.r * k2.r * outer.r * (k1.r + k2.r - outer.r)));
		return k3;
	}

}

#endif