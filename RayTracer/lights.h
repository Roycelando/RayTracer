#pragma once
#include"point.h"

class Light {
public:
	Point position;
	double intensity;

	Light() :position(0, 0, 10), intensity(1) {}
	Light(Point pos, double inten):position(pos), intensity(inten) {}


};

