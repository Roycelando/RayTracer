#pragma once

/*
		Defines my pixles
*/
typedef struct pixel {
	double r,g,b;

	pixel() : r(0), g(0), b(0) {}

	pixel(double r, double g, double b) : r(r), g(g), b(b) {}


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
