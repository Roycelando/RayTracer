#pragma once

typedef struct pixel {
	double r, g, b;

	pixel() : r(1), g(0), b(0) {}

	pixel(double rr, double gg, double bb) : r(rr), g(gg), b(bb) {}


};
