#pragma once
#include"point.h"

class Light {
public:
	Point position;
	double intensity;

	Light() :position(10,10, 3), intensity(2) {}
	Light(Point pos, double inten):position(pos), intensity(inten) {}


};

