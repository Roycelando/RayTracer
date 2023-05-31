#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<vector>
#include"pixel.h"
#include"vector.h"
#include"shape.h"
#include"camera.h"
#include "scene.h"
#include"lights.h"
#include<limits>
#include<algorithm>
//#include <windows.h>
#define background  Pixel(0,0,0);
#define background  Pixel(0.00078,0.1411,1);
//#include <Commdlg.h>
const double AIR	= 1.0003;



// function defitiion
void saveImage();
void colourPixel(Pixel* frameBuffer);
void printPixels(Pixel* frameBuffer);
Pixel rayTrace(Ray ray, double depth,double ni);
void loadScene();

//global variables
const int width = 1024;
const int height = 768;
const double aspectRatio = width / (double)height;
Scene scene =  Scene();

//Camera
Camera cam = Camera(0,0,1);
Pixel frameBuffer[(width*height)];



// viewport
double H = cam.origin.z * tan(cam.fov / 2.0);
double W = H * aspectRatio;

int main() {
	Vector l = Vector(0.707107,-0.707107,0);
	Vector n = Vector(0,1,0);
	double n1 = 0.9;
	double n2 = 1.0;

	Vector refract = getRefraction(l,n,n1,n2);
	Vector rfelct = getRefelction(l,n);
	refract.printVector();
	rfelct.printVector();



	loadScene();
	colourPixel(frameBuffer);
	saveImage();

	return 0;
}

/*
	This method is used to ray trace
*/
Pixel rayTrace(Ray ray, double depth, const double etai) {
	double tclose = std::numeric_limits<double>::max();
	Shape* hitObject = nullptr;
	Vector hitPoint;
	Vector normal;
	Pixel local; // local colour
	Pixel reflc; // reflection colour
	Pixel refrac; // refraction colour
	double epsilon = 0.000001; // large numbers cause saturation

	
	if (depth >= 7 || !(scene.intersect(ray, hitPoint, normal, tclose, hitObject))) 
		return background;
	
			double shade = scene.shade(hitObject,hitPoint,normal,ray);
			local = clamp(multPixels(hitObject->mat->colour,shade));

			//reflection
			double reflecRatio = hitObject->mat->reflec;
			if (reflecRatio>0) {
				Vector dirRef = getRefelction(ray.getDirection(),normal);
				Ray  reflect = Ray(dirRef,addVectors(hitPoint,epsilon));
				
				reflc = rayTrace(reflect,++depth,AIR);
				reflc = clamp(multPixels(reflc, reflecRatio));
			
			}

		
		    //refration 
			double etat = hitObject->mat->refrac;
			if (etat > 0) {
					Vector T = getRefraction(ray.getDirection(),normal,etai,etat);
					//std::cout<<"Magnitude: "<<T.magnitude()<<std::endl;

					if (T.magnitude() == 0.0) return clamp(addPixels(local, reflc));

					Ray refract = Ray(T,addVectors(hitPoint,epsilon));
					refrac = rayTrace(refract, ++depth, etat);
					refrac = clamp(multPixels(refrac, 0.3));
			}

			return	clamp(addPixels(addPixels(local, reflc),refrac));
}

Material* getMaterial(char mat, Pixel colour) {
	switch (mat) {
		case'R':
		case 'r': {
			return new Rubber(colour);

		}
		case'G':
		case 'g': {
			return new Glass(colour);

		}
		case'M':
		case 'm': {
			return new Metal(colour);

		}
	}
	return new Rubber(colour);
}

	
void loadScene() {

	std::string fileName;
	std::cout << "File Name: ";
	std::cin >> fileName;
	std::cout << std::endl;
	std::ifstream infile(fileName);

	double radius =-1;
	double x = -1, y = -1, z = -1;
	double r = -1, g = -1, b = -1;
	char m = 'g';
	double intensity = -1;
	Material* mat = nullptr;

	if (!infile.is_open()) 
		return;

		std::string shape;
		const std::string ignore = "//";
		std::string temp = "";

		while (!infile.eof() && infile >> shape) {

			//ignore comments
			if (shape.find(ignore) != std::string::npos) {
				std::getline(infile, temp);
				continue;
			}

			//sphere
			if (shape == "s" || shape == "S") {

				infile >> radius, infile >> x, infile >> y,infile >> z,infile >> m,infile >> r, infile >> g,infile >> b;
				
				Vector point = Vector(x,y,z); // creates the Point object
				Pixel pix = Pixel(r, g, b);
				mat = getMaterial(m,pix);
							
				std::cout << shape << " "<< radius<< " " << x<< " " << y << " "<< " "<< z <<" "<< m << " " << r << " "<< g <<" "<< b << std::endl;

				Shape* object = new Sphere(radius,point, *mat);

				scene.addObjects(object);
				

			}

			//light
			else if (shape == "l" || shape == "L") {

				infile >> intensity,infile >> x, infile >> y, infile >> z;

				std::cout << shape << " "<< intensity<< " " << x<< " " << y << " "<< " "<< z << std::endl;
				Light light = Light(x,y,z,intensity);
				scene.addLights(light);

			}
			
		}

	infile.close();

}


/*
* This method fills the frame buffer with results form the ray tracer
*/
void colourPixel(Pixel* frameBuffer) {
//#pragma omp paralle for
	for (int i = 0; i < height; i++ ) {
		for (int j = 0; j < width; j++) {
			double depth = 0;

			double valc = 2 * (j+0.5) / ((double)width);
			double valr = 2 * (i+0.5) / ((double)height);

			Ray ray = cam.castRay(W,H,valc,valr); // casting a ray toward current pixel
	
			frameBuffer[(i * width) + j] = rayTrace(ray,depth,AIR); 

		}

	}

}

/*
	saves frame buffer pixesl as a ppm file, hope you can open it, I probably should convert to a png, but I'm low on time
*/
void saveImage() {
	std::ofstream file("./image.ppm");
	file << "P3\n" << width << ' ' << height << "\n255\n";
	for (int i = 0; i <width*height; i++) {
		
		Pixel p = frameBuffer[i];

		unsigned int r = (int)(p.r * 255.999);
		unsigned int g = (int)(p.g * 255.999);
		unsigned int b = (int)(p.b * 255.999);

		file << r << ' ' << g << ' ' << b << '\n';
		
	}
	
	file.close();
	
}

/*
	This method prints to the consol pixels in my farmnebuffer.
	Used for debugging
*/
void printPixels(Pixel* frameBuffer) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Pixel p = frameBuffer[(i * height) + j];
			std::cout << "r: " << p.r<< " g: " <<p.g << " b: " <<p.b << std::endl;
		}
		std::cout << std::endl;
	}



}