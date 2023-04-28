#pragma once

#include"vector.h"
#include"ray.h"
#include"point.h"
#include<math.h>
#define PI 3.14159265358979323846


class Camera {
public:
	Vector right;
	Vector up;
	Vector forward;
	Point origin;
	double focalDistance = 1;

	double fov = PI/2;

	Camera() : right(1, 0, 0), up(0, 1, 0), forward(0, 0, 1),origin(0, 0, 1) {}

	Camera(double x, double y, double z): right(1,0,0), up(0,1,0), forward(0,0,1) {
		origin = Point(x,y,z);

	}

	Camera(Point origin): right(1,0,0), up(0,1,0), forward(0,0,1){
		this->origin = origin;
		focalDistance = abs(origin.z);

	}

	/*
		casting ray,
		
		calculation came from 	page 735 of [A.S. Glassner. An Introduction to Ray Tracing. Academic Press, 1989]

		don't full get it but it works!
	*/
	inline Ray castRay (double W, double H, double valc, double valr) {
		Vector rayDir;
		double uc = W * (valc - 1);
		Vector u = multVectors(right, uc);


		double vr = H * (valr - 1);
		Vector v = multVectors(up, vr);

		Vector n = multVectors(forward, -focalDistance);

		rayDir = addVectors(addVectors(n, u), v);


		return Ray(rayDir,origin);


	}

	Vector getForward() {
		return  forward;

	}




};

