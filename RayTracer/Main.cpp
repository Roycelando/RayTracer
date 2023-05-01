#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>
#include"pixel.h"
#include"vector.h"
#include"shape.h"
#include"camera.h"
#include "scene.h"
#include"lights.h"
#include<limits>
#include<algorithm>
#define background  pixel(0.2,0.7,0.8);


// function defitiion
void saveImage();
void colourPixel(pixel* frameBuffer);
void printPixels(pixel* frameBuffer);
pixel rayTrace(Ray ray, double depth);

//global variables
const int width = 1024;
const int height = 768;
const double aspectRatio = width / (double)height;
Scene scene =  Scene();


Camera cam = Camera(0,0,1);

pixel frameBuffer[(width*height)];
pixel p = pixel(1, 0, 1);
pixel p2 = pixel(1, 1, 1);
pixel p3 = pixel(1, 1, 0);

Material m = Rubber(p);
Material m2 = Rubber(p2);
Material m3 = Rubber(p3);




Sphere* sphere = new Sphere(1, Point(-2,0,-5));
Sphere* sphere2 = new Sphere(1, Point(2,0,-5),m);
Sphere* sphere3 = new Sphere(1, Point(0,1,-8),m2);
Sphere* sphere4 = new Sphere(1, Point(0,-3,-6),m3);

Light light = Light();
Point pos = Point(0, 0, -6);
Light light2 = Light(pos,1);




// viewport

double H = cam.origin.z * tan(cam.fov / 2.0);
double W = H * aspectRatio;

int main() {
	//std::cout << "r: " << sphere->mat->colour->r << " g: " << sphere->mat->colour->g<< " b: " << sphere->mat->colour->b<< std::endl;
//	std::cout << " ambient ratio: " << sphere->mat->ambR << std::endl;
	scene.addObjects(sphere);
	scene.addObjects(sphere2);
	scene.addObjects(sphere3);
	scene.addObjects(sphere4);


//	scene.addLights(light);
	scene.addLights(light2);


	


	
	colourPixel(frameBuffer);
	saveImage();

		return 0;
}


	pixel rayTrace(Ray ray, double depth) {
		double tfar = std::numeric_limits<double>::max();
		double tclose = std::numeric_limits<double>::max();
		Shape* hit;

		Point ri;
		Vector normal;
		pixel local;
		pixel ref = pixel(0,0,0);
		pixel refrac = pixel(0,0,0);
		hit = new Shape();

		if (depth > 4) {

			return background;

		}

		else {

			if (scene.intersect(ray,ri,normal,tclose,tfar,hit)) {

				//std::cout << "tclose: " << tclose << std::endl;
				

				Point hitPoint = ri;

	//				double I = std::min(scene.getLightIntensity(hit,hitPoint,normal,ray),(double)1.0);
				double I = std::min(std::max(scene.getLightIntensity(hit, hitPoint, normal, ray),(double)0),(double)1);

				double r = (hit->mat->colour->r)*I;
				double g = (hit->mat->colour->g)*I;
				double b = (hit->mat->colour->b)*I;

				local = pixel(r,g,b);


				//reflection
					ray.getDirection().normalizeVector();
					Vector dirRef = getRefelction(ray.getDirection(),normal);


					dirRef.normalizeVector();
					Point hitt = addPoints(hitPoint,(0.0001));

					Ray  reflect = Ray(dirRef,hitt);
			


				if (hit->mat->reflec>0) {
					
					ref = rayTrace(reflect,++depth);


					/*
					ref.r = std::max(std::min((double)ref.r, (double)1),(double)0);
					ref.g = std::max(std::min((double)ref.g, (double)1),(double)0);
					ref.b = std::max(std::min((double)ref.b, (double)1),(double)0);
					
					*/

					ref.g = std::min(std::max((double)ref.g, (double)0),(double)1);
					ref.g = std::min(std::max((double)ref.g, (double)0),(double)1);
					ref.b = std::min(std::max((double)ref.b, (double)0),(double)1);
					ref = multPixels(ref, 0.4);



				}




			//refration
			pixel result = 	addPixels(local, ref);
			result.r = std::min(std::max(result.r, (double)0), (double)1);
			result.g = std::min(std::max(result.g, (double)0), (double)1);
			result.b = std::min(std::max(result.b, (double)0), (double)1);

				return result;
			}

			else {
			
				return background	
			}


		}

	}

	





/*
* This method fills the frame buffer with the colour of our background
*/
void colourPixel(pixel* frameBuffer) {
	
	for (int i = 0; i < height; i++ ) {
		for (int j = 0; j < width; j++) {
			double depth = 0;

			double valc = 2 * j / ((double)width-1);
			double valr = 2 * i / ((double)height-1);

			Ray ray = cam.castRay(W,H,valc,valr);
	
			frameBuffer[(i * width) + j] = rayTrace(ray,depth);
			
		}

	}

}

void saveImage() {
	std::ofstream file("./image.ppm");
	file << "P3\n" << width << ' ' << height << "\n255\n";
	for (int i = 0; i < height*width; i++) {
		
		pixel p = frameBuffer[i];

		unsigned int r = (int)(p.r * 255.999);
		unsigned int g = (int)(p.g * 255.999);
		unsigned int b = (int)(p.b * 255.999);


		file << r << ' ' << g << ' ' << b << '\n';
		
	}

	
	file.close();
	
}

void printPixels(pixel* frameBuffer) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixel p = frameBuffer[(i * height) + j];
			std::cout << "r: " << p.r<< " g: " <<p.g << " b: " <<p.b << std::endl;
		}
		std::cout << std::endl;
	}



}