#pragma once
#include"pixel.h"
#include<iostream>


class Material {
	public:
		
		std::string name;
		//colour
		double ambR;
		double diffR;
		double specR;
		double specH;
		pixel* colour;

		// refelction and refraction coeficients 
		double reflec;
		double refrac;

		 Material() : ambR(1), diffR(1), specR(1), specH(1), reflec(0.3), refrac(0.3){
			colour = new pixel(1,0,0);
		}

		Material(double amb, double diff, double spec, pixel c) : ambR(amb), diffR(diff), specR(spec),specH(1){
			colour = new pixel(1,0,0);
		}

		Material(double amb, double diff, double spec, pixel c, double reflec, double refrac) : ambR(amb), diffR(diff), specR(spec),specH(1), reflec(reflec), refrac(refrac){
			colour = new pixel(1,0,0);
		}


};



class Rubber : public Material {
	public:	

	Rubber(pixel &c) {
		ambR = 0.3;
		diffR = 0.6;
		specR = 0.6;
		specH = 50;
		colour = &c;
		reflec = 0.8;
		refrac = 0.5;

		name = "rubber";

	}

	Rubber(){
		colour = new pixel(1, 0, 0);
		ambR = 0.3;
		diffR = 0.6;
		specR = 0.6;
		specH = 50;
		name = "rubber";
		reflec = 0.8;
		refrac = 0.5;


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

