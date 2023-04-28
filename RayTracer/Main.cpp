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


// function defitiion
void saveImage();
void raytrace(pixel* frameBuffer);
void printPixels(pixel* frameBuffer);

//global variables
const int width = 1024;
const int height = 768;
const double aspectRatio = width / (double)height;
Scene scene =  Scene();


Camera cam = Camera(0,0,1);

pixel frameBuffer[(width*height)];
pixel p = pixel(0, 0, 1);

Material m = Glass(p);



Sphere* sphere = new Sphere(3, Point(0,0,-5));
Sphere* sphere2 = new Sphere(10, Point(2,0,-15),m);
Light light = Light();


// viewport

double H = cam.origin.z * tan(cam.fov / 2.0);
double W = H * aspectRatio;

int main() {
	//std::cout << "r: " << sphere->mat->colour->r << " g: " << sphere->mat->colour->g<< " b: " << sphere->mat->colour->b<< std::endl;
	std::cout << " ambient ratio: " << sphere->mat->ambR << std::endl;
	scene.addObjects(sphere2);
	scene.addObjects(sphere);
	scene.addLights(light);


	


	
	raytrace(frameBuffer);
	saveImage();

		return 0;
}



/*
* This method fills the frame buffer with the colour of our background
*/
void raytrace(pixel* frameBuffer) {
	double tfar = std::numeric_limits<double>::max();
	double tclose = std::numeric_limits<double>::max();
	Shape* hit;

	for (int i = 0; i < height; i++ ) {
		for (int j = 0; j < width; j++) {

			double valc = 2 * j / ((double)width-1);
			double valr = 2 * i / ((double)height-1);

			Ray ray = cam.castRay(W,H,valc,valr);

		//	printVector(ray.getDirection());

			Point ri;
			Vector normal;
			pixel p;

			tclose = std::numeric_limits<double>::max();
			hit = new Shape();

			if (scene.intersect(ray,ri,normal,tclose,tfar,hit)) {

				//std::cout << "tclose: " << tclose << std::endl;

				double I = scene.getLightIntensity(hit);
				
				double r = (hit->mat->colour->r)*I;
				double g = (hit->mat->colour->g)*I;
				double b = (hit->mat->colour->b)*I;
				
				
;			
				p = { r,g,b};

		//		std::cout << hit.mat.name << std::endl;

			//	std::cout << "tclose: " << tclose << std::endl;

			}

			else {
				double r = i / (double)(height-1);
				double g = j / (double)(width-1);
				double b = 0.25;
				p = { r,g,b};

		}

			frameBuffer[(i * width) + j] = p;
			
		}

	//	std::cout<<std::endl<<std::endl;
	}

}

void saveImage() {
	std::ofstream file("./image.ppm");
	file << "P3\n" << width << ' ' << height << "\n255\n";
	for (int i = 0; i < height*width; i++) {
		
		pixel p = frameBuffer[i];

		int r = (int)(p.r * 255.9)%256;
		int g = (int)(p.g * 255.9)%256;
		int b = (int)(p.b * 255.9)%256;


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