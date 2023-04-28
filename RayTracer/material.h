#pragma once
#include"pixel.h"


class Material {
	public:
		std::string name;
		double ambR;
		double diffR;
		double specR;
		pixel* colour;

		 Material() : ambR(1), diffR(1), specR(1){
			colour = new pixel(1,0,0);
		}
		Material(double amb, double diff, double spec, pixel c) : ambR(amb), diffR(diff), specR(spec){
			colour = new pixel(1,0,0);
		}


};



class Rubber : public Material {
	public:	

	Rubber(pixel &c) {
		ambR = 0.2;
		diffR = 0.5;
		specR = 0.7;
		colour = &c;
		name = "rubber";

	}

	Rubber(){
		colour = new pixel(1, 0, 0);
		ambR = 0.2;
		diffR = 0.5;
		specR = 0.7;
		name = "rubber";

	}

};


class Glass : public Material {

public:
	Glass(pixel &c){
		ambR = 0.5;
		diffR = 0.8;
		specR = 1;
		colour = &c;
		name = "glass";
	}

	Glass(){
		colour = new pixel(1, 0, 0);
		ambR = 0.5;
		diffR = 0.8;
		specR = 1;
		name = "glass";

	}

	

};

class Metal : public Material {

};

