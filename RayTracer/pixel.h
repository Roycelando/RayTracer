#pragma once

typedef struct pixel {
	double r, g, b;

	pixel() : r(1), g(0), b(0) {}

	pixel(double rr, double gg, double bb) : r(rr), g(gg), b(bb) {}


};


pixel addPixels(pixel a, pixel b) {

	return pixel((a.r + b.r),( a.g + b.g), (a.b + b.b));


}

pixel multPixels(pixel a, pixel b) {

	return pixel((a.r * b.r),( a.g * b.g), (a.b * b.b));


}
pixel multPixels(pixel a, double b) {

	return pixel((a.r * b),( a.g * b), (a.b * b));


}
