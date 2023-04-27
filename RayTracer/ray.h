#pragma once
#include "vector.h"
#include "point.h"

class Ray {
		Vector dir; // Ray direction
		Point origin; // Ray origin
		
	public:
		Ray(Vector dir, Point origin) {
			this->dir = dir; 
			this->origin = origin;
		}

		Vector getDirection() {
			return dir;
		}
		
		Point getOrigin() {
			return origin;
		}

	Vector getDistanceT(double t){
		Vector direction = multVectors(dir,t);
		Vector rt = addVectors(direction,origin);

		return rt;

	}


};
