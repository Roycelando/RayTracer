#pragma once
#include "vector.h"

/*
	Defiens my light rays
*/
class Ray {
		Vector dir; // Ray direction
		Vector origin; // Ray origin
		
	public:
		Ray(Vector dir, Vector origin): dir(dir), origin(origin) {}

		Vector getDirection() {
			return dir;
		}
		
		Vector getOrigin() {
			return origin;
		}

	Vector getDistanceT(double t){
		dir.normalizeVector();
		Vector direction = multVectors(dir,t);
		Vector rt = addVectors(direction,origin);

		return rt;

	}


};
