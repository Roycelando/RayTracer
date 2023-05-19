#pragma once
#include"pixel.h"
#include<iostream>

/*

	Defines material for shapes
	
*/
class Material {
	public:
		//colour
		pixel colour;

		//lighting ratio 
		double ambR;
		double diffR;
		double specR;

		// specular thingy
		double specH;

		// refelction and refraction coeficients 
		double reflec;
		double refrac;

		 Material() : ambR(1), diffR(1), specR(1), specH(1), reflec(0.3), refrac(0.3){
			colour = pixel(1,0,0);
		}

		 Material(pixel &colour) : ambR(1), diffR(1), specR(1), specH(1), reflec(0.3), refrac(0.3){
			 this->colour = colour;
		}

		 Material(pixel &colour, double ambR, double diffR, double specR, double specH, double reflec, double refrac) : 
			 colour(colour), ambR(ambR), diffR(diffR), specR(specR), specH(specH), reflec(reflec), refrac(refrac){
		}

		Material(double r, double g, double b, double ambR, double diffR, double specR, double specH, double reflec, double refrac) : 
			 colour(pixel(r,g,b)), ambR(ambR), diffR(diffR), specR(specR), specH(specH), reflec(reflec), refrac(refrac){
		}

};

class Rubber : public Material {
	public:	

		pixel dColour = pixel(1,0,0);

		Rubber(pixel &colour) : Material(colour, 0.3, 0.6, 0.6, 20, 0, 0) {
		// colour, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio
		}

		Rubber(double r, double g, double b) : Material(r,g,b,0.3, 0.6, 0.6, 20, 0, 0) {
			//red, green, blue, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio

		}

		Rubber() : Material(dColour, 0.3, 0.6, 0.6, 20, 0, 0) {}

};


class Glass : public Material {
	public:

		pixel dColour = pixel(1,0,0);

		Glass(pixel &colour) : Material(colour, 0.4, 0.4, 0.4, 50, 0, 0.2) {
			// colour, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio

		}

		Glass() : Material(dColour, 0.4, 0.4, 0.4, 50, 1, 0.3) {
		//red, green, blue, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio

		}

		Glass(double r, double g, double b) : Material(r,g,b, 0.4, 0.4, 0.4, 50, 1, 0.3) {}
		

};


class Metal : public Material {
public:
	pixel dColour = pixel(1,0,0);

	Metal(pixel &colour) : Material(colour, 0.4, 0.4, 0.4, 50, 1, 0.3) {
	// colour, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio

	}

	Metal() : Material(dColour, 0.4, 0.4, 0.4, 50, 1, 0.3) {
	//red, green, blue, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio

	}

	Metal(double r, double g, double b) : Material(r, g, b, 0.4, 0.4, 0.4, 50, 1, 0.3) {}


};

