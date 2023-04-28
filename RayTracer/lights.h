#pragma once
#include"point.h"

class Light {
public:
	Point position;
	double intensity;

	Light() :position(10, 10, 10), intensity(5) {}
	Light(Point pos, double inten):position(pos), intensity(inten) {}


};

