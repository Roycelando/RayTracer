#pragma once
#include"point.h"
#include"ray.h"
#include"Vector.h"
#include<cmath>

class Shape {
	public:
		Point origin;
		Vector normal;
		
		Shape() {
			origin = Point();
			normal = Vector();
		}

		Shape(Point origin, Vector normal) {
			this->origin = origin;
			this->normal = normal;
		}

		virtual bool intersect(Ray& ray , Point& ri, Vector& normal) {
			return false;
		}

	private:

};


class Sphere: public Shape {
	public :
			double radius;

			Sphere() {
				radius = 1.0;
			}

			Sphere (double radius){
				this->radius = radius;
			}

		bool intersect(Ray& ray, Point& ri, Vector& normal) override{
			// A^2t + Bt +C = 0 
			Vector rayDir = ray.getDirection();
			Point rayOrigin = ray.getOrigin();

			double A = pow(rayDir.x, 2) + pow(rayDir.y, 2) + pow(rayDir.z,2);
			double B = 2 * ( (rayDir.x*(rayOrigin.x-origin.x)) + (rayDir.y*(rayOrigin.y-origin.y)) + (rayDir.z*(rayOrigin.z-origin.z)) );
			double C = pow((rayOrigin.x - origin.x), 2) + pow((rayOrigin.y - origin.y), 2) + pow((rayOrigin.z - origin.z), 2) - pow(radius, 2);

			double Disc = pow(B, 2) - (4 * C);

			if (Disc < 0)
				return false;
			
			double t0 = (- B - sqrt((B * B) - (4 * C))) / 2.0;
			double t1 = (- B + sqrt((B * B) - (4 * C))) / 2.0;

			if ((t0 < 0) && (t1 < 0))
				return false;

			double t =-1;

			if (t0 > 0)
				t = t0;
			else
				t = t1;

				double xi = rayOrigin.x + rayDir.x * t;
				double yi = rayOrigin.y + rayDir.y * t;
				double zi = rayOrigin.z + rayDir.z * t;
				
				ri = Point(xi,yi,zi); // intersect point of the ray on the sphere

				double xn = (xi - origin.x) / radius;
				double yn = (yi - origin.y) / radius;
				double zn = (zi - origin.z) / radius;

				normal = Vector(xn,yn,zn);



			return true;

		}

	private:

};

class Plane:Shape {
	public :

	private:

};

class Triangle:Shape {
	public :

	private:

};


