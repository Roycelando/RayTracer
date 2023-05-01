#pragma once
#include"pixel.h"
#include<iostream>

/*
	Defines material for shapes
*/

class Material {
	public:
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
		specH = 20;
		colour = &c;
		reflec = 0;
		refrac = 0;


	}

	Rubber(){
		colour = new pixel(1, 0, 0);
		ambR = 0.3;
		diffR = 0.6;
		specR = 0.6;
		specH = 20;
		reflec = 0;
		refrac = 0;


	}

};


class Glass : public Material {

public:
	Glass(pixel &c){
		ambR = 0.4;
		diffR = 0.4;
		specR = 0.4;
		specH = 50;
		reflec = 1;
		refrac = 0.3;


		colour = &c;
	}

	Glass(){
		colour = new pixel(0.2, 0.1, 0.8);
		ambR = 0.4;
		diffR = 0.4;
		specR = 0.4;
		specH = 50;
		reflec = 1;
		refrac = 0.3;



	}

};

class Metal : public Material {

};

