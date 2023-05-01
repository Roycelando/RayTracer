#pragma once
#include"point.h"
/*
 defines my light
*/
class Light {
public:
	Point position;
	double intensity;

	Light() :position(5,10, -2), intensity(2) {}
	Light(Point pos, double inten):position(pos), intensity(inten) {}


};

