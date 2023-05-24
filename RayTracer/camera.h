#pragma once

#include"vector.h"
#include"ray.h"
#include"point.h"
#include<math.h>
#define PI 3.14159265358979323846

/*
defines my camera
*/

class Camera {
public:
	Vector right;
	Vector up;
	Vector forward;
	Point origin;
	double focalDistance = 1;

	double fov = PI/2;

	Camera() : right(1, 0, 0), up(0, 1, 0), forward(0, 0, 1),origin(0, 0, 1) {}

	Camera(double x, double y, double z): right(1,0,0), up(0,1,0), forward(0,0,1), origin(x,y,z) {
				//	std::cout << " x: " << up.x << " y: " << up.y << " z: " << up.z <<  std::endl;

	}

	Camera(Point origin) : right(1, 0, 0), up(0, 1, 0), forward(0, 0, 1), origin(origin.x,origin.y,origin.z) {
				focalDistance = abs(origin.z);
				//std::cout << " x: " << up.x << " y: " << up.y << " z: " << up.z <<  std::endl;
	}

	/*
		casting ray,
		
		calculations came from 	page 735 of F.S. Hill Jr and S.M. Kelley. Computer Graphics using OpenGL, 3e. Prentice Hall, 2007.

		don't fully get it but it works!
	*/
	inline Ray castRay (double W, double H, double valc, double valr) {

	//	std::cout << " valc: "<< valc << " valr: " << valr << std::endl;

		Vector rayDir;
		double uc = W * (valc - 1);
		Vector u = multVectors(right, uc);


		double vr = -H * (valr - 1);
		Vector v = multVectors(up, vr);

		Vector n = multVectors(forward, -focalDistance);

		rayDir = addVectors(addVectors(n, u), v);



		return Ray(rayDir,origin);


	}

	Vector getForward() {
		return  forward;

	}




};

