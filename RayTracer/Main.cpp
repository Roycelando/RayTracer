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
#define background  Pixel(0.00078,0.1411,1);
#define background  Pixel(0,0,0);
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
	// saving image
	loadScene();
	colourPixel(frameBuffer);
	saveImage();

	return 0;
}

/*
	This method is used to ray trace
*/
Pixel rayTrace(Ray ray, double depth, double ni) {
	double tclose = std::numeric_limits<double>::max();
	Shape* hitObject = nullptr;

	Vector hitPoint;
	Vector normal;

	Pixel local; // local colour
	Pixel ref; // reflection colour
	Pixel refrac; // refraction colour
	double epsilon = 0.00001; // large numbers cause saturation

	
		if (depth<4 && scene.intersect(ray,hitPoint,normal,tclose,hitObject)) {
			

			//std::cout << "mag: " << ray.getDirection().magnitude() << std:: endl;
			 double I = scene.shade(hitObject,hitPoint,normal,ray);
			// double I = std::min((std::max(scene.getLightIntensity(hit, hitPoint, normal, ray),(double)0)),(double)1);

			double r = (hitObject->mat->colour.r)*I;
			double g = (hitObject->mat->colour.g)*I;
			double b = (hitObject->mat->colour.b)*I;


			local = Pixel(r,g,b);

			//printPixel(local);


			//reflection

			if (hitObject->mat->reflec>0) {
				Vector dirRef = getRefelction(ray.getDirection(),normal);
				Vector hitPointEpsilon = addVectors(hitPoint,epsilon); //pushes the ray a bit so it doesn't intersect with its starting object
				Ray  reflect = Ray(dirRef,hitPointEpsilon);
				
					
				ref = rayTrace(reflect,++depth,hitObject->mat->refrac);

				ref = multPixels(ref, hitObject->mat->reflec);

				ref.r = std::min(std::max(ref.r, 0.0),1.0);
				ref.g = std::min(std::max(ref.g, 0.0),1.0);
				ref.b = std::min(std::max(ref.b, 0.0),1.0);

				
			}

			//refraction equation: T = alpha*I + beta *N, T is the transmission vector

			double nt = AIR;

			if(ni == AIR)
				nt = hitObject->mat->refrac; // material transmission

			if ( false) {
				double nit = ni / nt; // snells law
				ray.getDirection().normalizeVector(); // normalizing the ray just incase its not normalized yet
				Vector nitI = multVectors(ray.getDirection(),nit); // the ray is the incident ray, so we multiply it by nit
				nitI.normalizeVector();// normalize this new vecotr since this needs to be a unit vector


				double Ci = dotVectors(multVectors(normal, -1), ray.getDirection()); // Ci = cos(thea i) = N(unit vector) * -I(unit vector)
				double nitPow = pow(nit,2);
				double ciPow = pow(Ci,2);
				double root = sqrt((1 + (nitPow * (ciPow - 1))));

				if (root>0) {

					double beta = (nit * Ci) - root;

					Vector N = multVectors(normal,beta); // Normal vector
					Vector T = addVectors(nitI,N); // Transmissin vector

					T.normalizeVector(); // want the unit vector of the transmison vector 
					N.normalizeVector(); // wnat the unit vector of the normal vector 

					Ray refract = Ray(T,addVectors(hitPoint, 0.011));

					if (ni == AIR ) { 
						refrac = rayTrace(refract,++depth,nt);

					}

				//	else if (hit->name =="Sphere" && ni == hit->mat->refrac) {
					else{
						refrac = rayTrace(refract,++depth,AIR); 
					}

					refrac.r = std::min(std::max((double)refrac.r, (double)0),(double)1);
					refrac.g = std::min(std::max((double)refrac.g, (double)0),(double)1);
					refrac.b = std::min(std::max((double)refrac.b, (double)0),(double)1);

				}

			
			}


			Pixel result = 	addPixels(local, ref);
			result.r = std::min(std::max(result.r, (double)0), (double)1);
			result.g = std::min(std::max(result.g, (double)0), (double)1);
			result.b = std::min(std::max(result.b, (double)0), (double)1);

			return result;
		}

			return background;

}

	
void loadScene() {

	static const int max_line = 65536;

	std::string fileName;
	std::cout << "File Name: ";
	std::cin >> fileName;
	std::cout << std::endl;
	std::ifstream infile(fileName);

	if (infile.is_open()) {

		std::string shape;
		const std::string ignore = "//";
		std::string temp = "";

		while (!infile.eof() && infile >> shape) {

			if (shape.find(ignore) != std::string::npos) {
				std::getline(infile, temp);
			}
			else {

				if (shape == "s" || shape == "S") {

					double radius =-1;
					double x = -1;
					double y = -1;
					double z = -1;
					char m = 'g';
					double r = -1;
					double g = -1;
					double b = -1;
					Material* mat = nullptr;

					infile >> radius;
					infile >> x;
					infile >> y;
					infile >> z;
					infile >> m;
					infile >> r;
					infile >> g;
					infile >> b;
					
					Vector point = Vector(x,y,z); // creates the Point object
					Pixel pix = Pixel(r, g, b);
					if (m == 'r') {

						mat = new Rubber(pix);
					}
					else if (m=='g') {
						mat = new Glass(pix);
					}

					else if (m == 'm') {
						mat = new Metal(pix);

					}
					
					std::cout << shape << " "<< radius<< " " << x<< " " << y << " "<< " "<< z <<" "<< m << " " << r << " "<< g <<" "<< b << std::endl;

					Shape* object = new Sphere(radius,point, *mat);

					scene.addObjects(object);
					
	

				}

				else if (shape == "l" || shape == "L") {

					double intensity = -1;
					double x = -1;
					double y = -1;
					double z = -1;

					infile >> intensity;
					infile >> x;
					infile >> y;
					infile >> z;

					std::cout << shape << " "<< intensity<< " " << x<< " " << y << " "<< " "<< z << std::endl;
					Light light = Light(x,y,z,intensity);
					scene.addLights(light);



				}

			}
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