#pragma once
#include"pixel.h"
#include<iostream>


class Material {
	public:
		
		std::string name;
		double ambR;
		double diffR;
		double specR;
		double specH;
		pixel* colour;

		 Material() : ambR(1), diffR(1), specR(1), specH(1){
			colour = new pixel(1,0,0);
		}
		Material(double amb, double diff, double spec, pixel c) : ambR(amb), diffR(diff), specR(spec),specH(1){
			colour = new pixel(1,0,0);
		}


};



class Rubber : public Material {
	public:	

	Rubber(pixel &c) {
		ambR = 0.5;
		diffR = 0.5;
		specR = 0.5;
		specH = 10;
		colour = &c;
		name = "rubber";

	}

	Rubber(){
		colour = new pixel(1, 0, 0);
		ambR = 0.5;
		diffR = 0.5;
		specR = 0.5;
		specH = 10;
		name = "rubber";

	}

};


class Glass : public Material {

public:
	Glass(pixel &c){
		ambR = 0.6;
		diffR = 0.6;
		specR = 0.9;
		specH = 1;
		colour = &c;
		name = "glass";
	}

	Glass(){
		colour = new pixel(1, 0, 0);
		ambR = 0.6;
		diffR = 0.6;
		specR = 0.9;
		specH = 1;
		name = "glass";

	}

};

class Metal : public Material {

};

