#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>
#include"pixel.h"
#include"vector.h"
#include"shape.h"
#include"camera.h"


// function defitiion
void saveImage();
void createBackground(pixel* frameBuffer);
void printPixels(pixel* frameBuffer);

//global variables
const int width = 1024;
const int height = 768;
const double aspectRatio = width / (double)height;


Camera cam = Camera(0,0,1);

pixel frameBuffer[(width*height)];

Sphere sphere = Sphere(3, Point(0,0,-10));


// viewport

double H = cam.origin.z * tan(cam.fov / 2.0);
double W = H * aspectRatio;

int main() {

	
	createBackground(frameBuffer);
	saveImage();

		return 0;
}



/*
* This method fills the frame buffer with the colour of our background
*/
void createBackground(pixel* frameBuffer) {
	for (int i = 0; i < height; i++ ) {
		for (int j = 0; j < width; j++) {

			double valc = 2 * j / ((double)width-1);
			double valr = 2 * i / ((double)height-1);

			Ray ray = cam.castRay(W,H,valc,valr);

			//printVector(ray.getDirection());

			Point ri;
			Vector normal;
			pixel p;


			if (sphere.intersect(ray,ri,normal)) {

				float r = 1;
				float g = 0;
				float b = 0;
				p = { r,g,b};

			}

			else {
				double r = i / (double)(height-1);
				double g = j / (double)(width-1);
				double b = 0.25;
				p = { r,g,b};

		}

			frameBuffer[(i * width) + j] = p;
			
		}

		std::cout<<std::endl<<std::endl;
	}

}

void saveImage() {
	std::ofstream file("./image.ppm");
	file << "P3\n" << width << ' ' << height << "\n255\n";
	for (int i = 0; i < height*width; i++) {
		
		pixel p = frameBuffer[i];

		int r = p.r * 255.9;
		int g = p.g * 255.9;
		int b = p.b * 255.9;


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