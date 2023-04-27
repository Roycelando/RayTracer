#pragma once
#include"pixel.h"


class Material {
	public:
		std::string name;
		double ambR;
		double diffR;
		double specR;
		pixel colour;

		Material() : ambR(1), diffR(1), specR(1), colour(1,0,1){}
		Material(double amb, double diff, double spec, pixel c) : ambR(amb), diffR(diff), specR(spec),colour(c){}


};



class Rubber : public Material {
	public:	
	Rubber(pixel c) {
		ambR = 0.2;
		diffR = 0.5;
		specR = 0.7;
		colour = c;
		name = "rubber";

	}

	Rubber(){
		colour = pixel(1, 0, 0);
		ambR = 0.2;
		diffR = 0.5;
		specR = 0.7;
		name = "rubber";

	}

};


class Glass : public Material {
	std::string name = "glass";

public:
	Glass(pixel c){
		ambR = 0.7;
		diffR = 0.8;
		specR = 1;
		colour = c;

	}

	Glass(){
		colour = pixel(1, 0, 0);
		ambR = 0.7;
		diffR = 0.8;
		specR = 1;

	}

	

};

class Metal : public Material {

};

