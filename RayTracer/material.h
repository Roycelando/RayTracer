#pragma once
#include"pixel.h"
#include<iostream>

/*

	Defines material for shapes
	
*/
class Material {
	public:
		//colour
		Pixel colour;

		//lighting ratio 
		double ambR;
		double diffR;
		double specR;
		double refracR;

		// specular thingy
		double specH;

		// refelction and refraction coeficients 
		double reflec;
		double refrac;

		 Material() : ambR(1), diffR(1), specR(1), specH(1), reflec(0.3), refrac(0.3), refracR(0){
			colour = Pixel(1,0,0);
		}

		 Material(Pixel &colour) : ambR(1), diffR(1), specR(1), specH(1), reflec(0.3), refrac(0.3), refracR(0){
			 this->colour = colour;
		}

		 Material(Pixel &colour, double ambR, double diffR, double specR, double specH, double reflec, double refrac, double refracR) : 
			 colour(colour), ambR(ambR), diffR(diffR), specR(specR), specH(specH), reflec(reflec), refrac(refrac), refracR(refracR){
		}

		Material(double r, double g, double b, double ambR, double diffR, double specR, double specH, double reflec, double refrac, double refracR) : 
			 colour(Pixel(r,g,b)), ambR(ambR), diffR(diffR), specR(specR), specH(specH), reflec(reflec), refrac(refrac),refracR(0){
		}

};

class Rubber : public Material {
	public:	

		Pixel dColour = Pixel(1,0,0);

		Rubber(Pixel &colour) : Material(colour, 0.2, 1.4, 0.3, 10, 0, 1.0,0.0) {
		// colour, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio
		}

		Rubber(double r, double g, double b) : Material(r,g,b,0.6, 0.6, 0.6, 20, 0, 0,0) {
			//red, green, blue, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio

		}

		Rubber() : Material(dColour, 0.6, 0.6, 0.6, 20, 0, 0,0) {}

};


class Glass : public Material {
	public:

		Pixel dColour = Pixel(1,0,0);

		Glass(Pixel &colour) : Material(colour, 0.1, 0, 0.9, 125, 0.1, 1.2, 1.0) {
			// colour, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio
		}

		Glass() : Material(dColour, 0, 0, 0.9, 125, 0, 1.5,0.8) {
		//red, green, blue, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio

		}

		Glass(double r, double g, double b) : Material(r,g,b, 0.5, 0, 1.0, 125, 0, 1.5, 0) {}
		
};

class Mirror : public Material {
	public:

		Pixel dColour = Pixel(1,0,0);

		Mirror(Pixel &colour) : Material(colour, 0, 0, 16.0, 1425, 0.8, 1.0, 0.0) {
			// colour, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refract index, refraction ratio

		}

		Mirror() : Material(dColour, 0.5, 0.0, 0.8, 1425, 1, 1.5,0) {
		//red, green, blue, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio

		}

		Mirror(double r, double g, double b) : Material(r,g,b, 0.5, 0.0, 1.0, 1425, 1, 1.5,0.0) {}
		
};

class Ivory : public Material {
	public:
		Pixel dColour = Pixel(1,0,0);

		Ivory(Pixel &colour) : Material(colour, 0.0, 0.9, 0.5, 50, 0.1, 1.0,0.0) {
			// colour, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio

		}

		Ivory() : Material(dColour, 0.5, 0, 0.8, 100, 1, 1.5,0) {
		//red, green, blue, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio

		}

		Ivory(double r, double g, double b) : Material(r,g,b, 0.5, 0, 1.0, 1000, 1, 1.5,0) {}
		
};

class Metal : public Material {
public:
	Pixel dColour = Pixel(1,0,0);

	Metal(Pixel &colour) : Material(colour, 0.4, 0.4, 0.4, 50, 1, 0.3,0) {
	// colour, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio

	}

	Metal() : Material(dColour, 0.4, 0.4, 0.4, 50, 1, 0.3,0) {
		//red, green, blue, abmient Ratio, Diffuse Ratio, Specular Ratio, Specular Highlight, refelection ratio, refraction ratio
	}

	Metal(double r, double g, double b) : Material(r, g, b, 0.4, 0.4, 0.4, 50, 1, 0.3,0) {}


};


