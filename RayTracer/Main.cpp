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
#define background  pixel(0,0,0);



// function defitiion
void saveImage();
void colourPixel(pixel* frameBuffer);
void printPixels(pixel* frameBuffer);
pixel rayTrace(Ray ray, double depth,double ni);

//global variables
const int width = 1024;
const int height = 768;
const double aspectRatio = width / (double)height;
Scene scene =  Scene();

//Camera
Camera cam = Camera(0,0,1);

pixel frameBuffer[(width*height)];

//settting up scene
pixel p = pixel(0, 0, 1);
pixel p2 = pixel(0.658, 0.690, 0.698);
pixel p3 = pixel(0.7, 0.1, 0.3);
pixel p4 = pixel(0.2, 0.2, 0.8);
pixel p5 = pixel(0.8, 0.3, 0.5);

Material m = Glass(p);
Material m2 = Glass(p2);
Material m3 = Rubber(p3);
Material m4 = Glass(p4);
Material m5 = Glass(p5);




Sphere* sphere = new Sphere(2, Point(-5,0,-10),m);
Sphere* sphere2 = new Sphere(2, Point(3,0,-5),m3);
Sphere* sphere3 = new Sphere(2, Point(0,-3,-15),m2);
Sphere* sphere4 = new Sphere(3, Point(0,5,-20),m4);

//Plane* plane = new Plane();

//Sphere* sphere3 = new Sphere(1, Point(0,1,-8),m2);

Point pos = Point(7, 5, 2);
Point pos2 = Point(0, -2, -20);
Point pos3 = Point(0, 5, -10);
Point pos4 = Point(0, 5, 3);


Light light = Light(pos,4);
Light light2 = Light(pos2,7);
Light light3 = Light(pos3,3);
Light light4 = Light(pos4,4);


// viewport

double H = cam.origin.z * tan(cam.fov / 2.0);
double W = H * aspectRatio;

int main() {
	
// placing objects in scene
	scene.addObjects(sphere);
	scene.addObjects(sphere2);
	scene.addObjects(sphere3);
	scene.addObjects(sphere4);

//placing lights
	scene.addLights(light);
	scene.addLights(light2);

//	scene.addLights(light3);
//	scene.addLights(light4);


// saving image
	colourPixel(frameBuffer);
	saveImage();

		return 0;
}

	/*
		This method is used to tray trace
	*/
	pixel rayTrace(Ray ray, double depth, double ni) {
		double tfar = std::numeric_limits<double>::max();
		double tclose = std::numeric_limits<double>::max();
		Shape* hit;

		Point ri;
		Vector normal;
		pixel local;
		pixel ref = pixel(0,0,0);
		pixel refrac = pixel(0,0,0);
		hit = new Shape();

		if (depth > 8) {

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


			


				if (hit->mat->reflec>0) {

				//reflection

					ray.getDirection().normalizeVector();
					Vector dirRef = getRefelction(ray.getDirection(),normal);
					dirRef.normalizeVector();
					Point hitt = addPoints(hitPoint,(0.00011));

					Ray  reflect = Ray(dirRef,hitt);
					
					ref = rayTrace(reflect,++depth,hit->mat->refrac);


					ref.r = std::min(std::max((double)ref.r, (double)0),(double)1);
					ref.g = std::min(std::max((double)ref.g, (double)0),(double)1);
					ref.b = std::min(std::max((double)ref.b, (double)0),(double)1);
					ref = multPixels(ref, hit->mat->reflec);



				}

				double nt = hit->mat->refrac;

				if (nt>0) {
					double nit = ni / nt;
					ray.getDirection().normalizeVector();
					Vector nitI = multVectors(ray.getDirection(),nit);
					nitI.normalizeVector();


					double Ci = dotVectors(multVectors(normal, -1), ray.getDirection());
					double nitPow = pow(nit,2);
					double ciPow = pow(Ci,2);

					double beta = nit * Ci - sqrt((1 + nitPow * (ciPow - 1)));
					Vector N = multVectors(normal,beta);


					Vector T = addVectors(nitI,N);
					T.normalizeVector();

					Ray refract = Ray(T,addPoints(hitPoint, 0.00011));

					if (ni == nt)
						ni = 1;

					
					refrac = rayTrace(refract,++depth,nt);

					refrac.r = std::min(std::max((double)refrac.r, (double)0),(double)1);
					refrac.g = std::min(std::max((double)refrac.g, (double)0),(double)1);
					refrac.b = std::min(std::max((double)refrac.b, (double)0),(double)1);

				
				}




			//refration
			pixel result = 	addPixels(addPixels(local, ref),refrac);
			result.r = std::min(std::max(result.r, (double)0), (double)1);
			result.g = std::min(std::max(result.g, (double)0), (double)1);
			result.b = std::min(std::max(result.b, (double)0), (double)1);

				return result;
			}

			else {
			
				return background;
			}


		}

	}

	





/*
* This method fills the frame buffer with results form the ray tracer
*/
void colourPixel(pixel* frameBuffer) {
	
	for (int i = 0; i < height; i++ ) {
		for (int j = 0; j < width; j++) {
			double depth = 0;
			double air = 1.0;

			double valc = 2 * j / ((double)width-1);
			double valr = 2 * i / ((double)height-1);

			Ray ray = cam.castRay(W,H,valc,valr);
	
			frameBuffer[(i * width) + j] = rayTrace(ray,depth,air);
			
		}

	}

}

/*
	saves frame buffer pixesl as a ppm file, hope you can open it, I probably should convert to a png, but I'm low on time
*/
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
/*
This method prints pixels in my farmnebuffer, used for debugging
*/
void printPixels(pixel* frameBuffer) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixel p = frameBuffer[(i * height) + j];
			std::cout << "r: " << p.r<< " g: " <<p.g << " b: " <<p.b << std::endl;
		}
		std::cout << std::endl;
	}



}