#pragma once
#include"point.h"
#include"ray.h"
#include"Vector.h"
#include<cmath>
#include"material.h"
/*
	Defines my shapes
*/
class Shape {
	public:
		Point origin;
		Vector normal;
		Material* mat;
		
		Shape() {
			origin = Point();
			normal = Vector();
			mat = new Rubber();
		}

		Shape(Point origin) {
			this->origin = origin;
			mat = new Rubber();
		}

		Shape(Point origin, Material mat) {
			this->origin = origin;
			this->mat = &mat;
		}

		Shape(double x, double y, double z): origin(x,y,z) {
			
		}


		virtual inline bool intersect(Ray& ray , Point& ri, Vector& normal, double& tclose, double& tfar, Shape* & hit, Shape* & curObj) {
			//std::cout << "is my hunc corrcect?" << std::endl;
			return false;
		}

		virtual	inline bool intersect(Ray& ray, Point& intersect) {
			return false;
		}

	private:

};


class Sphere: public Shape {
	public :
			double radius;

		Sphere() {
			radius = 1.0;
			origin = Point(0,0,-2);
			mat = new Rubber();

		}
			
		Sphere (double radius, Point origin){
				this->radius = radius;
				this->origin = origin;
				mat = new Glass();

		}

		Sphere (double radius, Point origin, Material& m){
			this->radius = radius;
			this->origin = origin;
			mat = &m;
		}


		inline bool intersect(Ray& ray, Point& ri, Vector& normal,double& tclose, double& tfar,Shape* & hit, Shape* & curObj) override {
			// A^2t + Bt +C = 0 
			Vector rayDir = ray.getDirection();
			Point rayOrigin = ray.getOrigin();
			rayDir.normalizeVector();


			double A = pow(rayDir.x, 2) + pow(rayDir.y, 2) + pow(rayDir.z,2);
			double B = 2 * ( (rayDir.x*(rayOrigin.x-origin.x)) + (rayDir.y*(rayOrigin.y-origin.y)) + (rayDir.z*(rayOrigin.z-origin.z)) );
			double C = pow((rayOrigin.x - origin.x), 2) + pow((rayOrigin.y - origin.y), 2) + pow((rayOrigin.z - origin.z), 2) - pow(radius, 2);


			double Disc = pow(B, 2) - (4 * C);


			if (Disc < 0)
				return false;
			
			double t0 = (- B - sqrt((B * B) - (4 * C))) / 2.0;
			double t1 = (- B + sqrt((B * B) - (4 * C))) / 2.0;



			double t =-1;

			if (t0 > 0.001)
				t = t0;
			else if (t1 > 0.001)
				t = t1;
			else
				return false;


			 if(t> tfar || t > tclose) 
				 return false;

			 tclose = t;
			 hit = curObj;

				double xi = rayOrigin.x + (rayDir.x * t);
				double yi = rayOrigin.y + (rayDir.y * t);
				double zi = rayOrigin.z + (rayDir.z * t);

				
				ri = Point(xi,yi,zi); // intersect point of the ray on the sphere

				double xn = (xi - origin.x) / radius;
				double yn = (yi - origin.y) / radius;
				double zn = (zi - origin.z) / radius;

				normal = Vector(xn,yn,zn);

				normal.normalizeVector();



			return true;

		}
	inline bool intersect(Ray& ray, Point& intersect) override {
			// A^2t + Bt +C = 0 
			Vector rayDir = ray.getDirection();
			Point rayOrigin = ray.getOrigin();
			rayDir.normalizeVector();


			double A = pow(rayDir.x, 2) + pow(rayDir.y, 2) + pow(rayDir.z,2);
			double B = 2 * ( (rayDir.x*(rayOrigin.x-origin.x)) + (rayDir.y*(rayOrigin.y-origin.y)) + (rayDir.z*(rayOrigin.z-origin.z)) );
			double C = pow((rayOrigin.x - origin.x), 2) + pow((rayOrigin.y - origin.y), 2) + pow((rayOrigin.z - origin.z), 2) - pow(radius, 2);


			double Disc = pow(B, 2) - (4 * C);


			if (Disc < 0)
				return false;

			double t0 = (- B - sqrt((B * B) - (4 * C))) / 2.0;
			double t1 = (- B + sqrt((B * B) - (4 * C))) / 2.0;
			double t = -1;

			if (t0 > 0.001)
				t = t0;
			else if (t1 > 0.001)
				t = t1;
			else
				return false;


			double xi = rayOrigin.x + (rayDir.x * t);
			double yi = rayOrigin.y + (rayDir.y * t);
			double zi = rayOrigin.z + (rayDir.z * t);


			intersect = Point(xi, yi, zi); // intersect point of the ray on the sphere



		
			return true;

			
		}

	private:

};
/*
	Don't try to render planes, I didn't get it to work on time
*/
class Plane:public Shape {
	public :
		double distance;

		Plane(Vector norm, Point org,double distance){
			normal = norm;
			origin = org;
			this->distance = distance;
		}

		Plane() {
			normal = Vector(0,1,0);
			Point(0,0,0);
			distance = 10;
			mat = new Rubber();

		}

		inline bool intersect(Ray& ray, Point& ri, Vector& normal, double& tclose, double& tfar, Shape*& hit, Shape*& curObj) {
			ray.getDirection().normalizeVector();
			

			 double PnRd = dotVectors(this->normal,ray.getDirection());
			 //std::cout << "PnRd: " << PnRd << std::endl;

			 if (PnRd >=0) {
				 return false;

			 }


			 Vector Ro = convertToVector(ray.getOrigin());
			 Ro.normalizeVector();
			 double t = -1*(dotVectors(this->normal, Ro) + this->distance)/ PnRd;


			 if (t<0 || t>tfar) 
				 return false;

			 ray.getDirection().normalizeVector();
			 Vector r = ray.getDirection();
			 Point o = ray.getOrigin();
				
			 ri = Point((o.x + (r.x*t)),(o.y+(r.y*t)),(o.z+(r.z*t)));
			 //normal = subPointsV( addPoints(ri,(0,5,0)),ri);
			 normal = this->normal;
			 normal.normalizeVector();



				return true;
		}

		virtual	inline bool intersect(Ray& ray, Point interesect,double tfar) {

			return false;
		}

};

class Triangle:Shape {
	public :
			


	private:

};


