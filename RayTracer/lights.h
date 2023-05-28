#pragma once
/*
 defines my light
*/
class Light {
public:
	Vector position;
	double intensity;

	Light() :position(5,10, -2), intensity(2) {}
	Light(double x,double y, double z, double inten):position(x,y,z), intensity(inten) {}
	Light(Vector pos, double inten):position(pos), intensity(inten) {}


};

