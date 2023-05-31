#pragma once

/*
		Defines my pixles
*/
typedef struct Pixel {
	double r,g,b;

	Pixel() : r(0), g(0), b(0) {}

	Pixel(double r, double g, double b) : r(r), g(g), b(b) {}


};

void printPixel(Pixel p) {
	std::cout << "(" << p.r << " , " << p.g << " , " << p.b << ")" << std::endl;
}

Pixel addPixels(Pixel a, Pixel b) {
	return Pixel((a.r + b.r),( a.g + b.g), (a.b + b.b));
}

Pixel multPixels(Pixel a, Pixel b) {
	return Pixel((a.r * b.r),( a.g * b.g), (a.b * b.b));
}

Pixel multPixels(Pixel a, double b) {
	return Pixel((a.r * b),( a.g * b), (a.b * b));
}

Pixel clamp(Pixel p) {
	p.r = std::min(std::max(p.r, 0.0), 1.0);
	p.g = std::min(std::max(p.g, 0.0), 1.0);
	p.b = std::min(std::max(p.b, 0.0), 1.0);

	return p;

}
