#pragma once
#include "vector.h"
#include "point.h"

class Ray {
		Vector dir; // Ray direction
		Point origin; // Ray origin
		
		double t =-1; // how far along you are on the ray R(t) = Ro + Rd*t; Ro = origin, Rd = dir, t=t

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


};
