#pragma once
#include"ray.h"
#include"Vector.h"
#include<cmath>
#include"material.h"
/*
	Defines my shapes
*/
class Shape {
	public:
		Vector origin;
		Material* mat;
		
		Shape(): origin(0,0,0), mat(new Rubber) {
		}

		Shape(Vector origin): origin(origin), mat(new Rubber) {

		}

		Shape(Vector origin, Material& mat): origin(origin), mat(&mat) {
		
		}


		virtual inline bool intersect(Ray& ray , Vector& ri, Vector& normal, double& tclose, Shape* & closestObj, Shape* & curObj) {
			return false;
		}

		virtual	inline bool intersect(Ray& ray, Vector& intersect) {
			return false;
		}

	private:

};


class Sphere: public Shape {
	public :
			double radius;

		Sphere():radius(1), Shape() {}
			
		Sphere (double radius, Vector origin): radius(radius),Shape(origin){}

		Sphere (double radius, Vector origin, Material& m): radius(radius), Shape(origin, m){}


	inline bool intersect(Ray& ray, Vector& hitPoint, Vector& normal,double& tclose,Shape* & closestObj, Shape* & curObj) override {
			// A^2t + Bt +C = 0 
			double tfar = std::numeric_limits<double>::max();
			Vector rayDir = ray.getDirection();
			Vector rayOrigin = ray.getOrigin();
			rayDir.normalizeVector();
			double epsilon = 0.001;


			double B = 2 * ( (rayDir.x*(rayOrigin.x-origin.x)) + (rayDir.y*(rayOrigin.y-origin.y)) + (rayDir.z*(rayOrigin.z-origin.z)) );
			double C = pow((rayOrigin.x - origin.x), 2) + pow((rayOrigin.y - origin.y), 2) + pow((rayOrigin.z - origin.z), 2) - pow(radius, 2);


			double Disc = pow(B, 2) - (4* C);


			if (Disc < 0)
				return false;

			double t0 = (- B - sqrt((B * B) - (4*C))) / 2.0;
			double t1 = (- B + sqrt((B * B) - (4*C))) / 2.0;



			double t =-1;

			if (t0 > epsilon)
				t = t0;
			else if (t1 > epsilon)
				t = t1;
			else
				return false;


			 if(t> tfar || t > tclose) 
				 return false;

			 tclose = t;
			 closestObj = curObj;

					
				hitPoint = ray.getDistanceT(tclose); // intersect point of the ray on the sphere

				double xn = (hitPoint.x - origin.x)/radius;
				double yn = (hitPoint.y - origin.y)/radius;
				double zn = (hitPoint.z - origin.z)/radius;

				normal = Vector(xn,yn,zn);


			return true;

	}
	inline bool intersect(Ray& ray, Vector& intersect) override {
			double epsilon = 0.001;
			Vector rayDir = ray.getDirection();
			Vector rayOrigin = ray.getOrigin();
			rayDir.normalizeVector();


			double B = 2 * ( (rayDir.x*(rayOrigin.x-origin.x)) + (rayDir.y*(rayOrigin.y-origin.y)) + (rayDir.z*(rayOrigin.z-origin.z)) );
			double C = pow((rayOrigin.x - origin.x), 2) + pow((rayOrigin.y - origin.y), 2) + pow((rayOrigin.z - origin.z), 2) - pow(radius, 2);


			double Disc = pow(B, 2) - (4*C);


			if (Disc < 0)
				return false;

			double t0 = (- B - sqrt((B * B) - (4 * C))) / 2.0;
			double t1 = (- B + sqrt((B * B) - (4 * C))) / 2.0;
			double t = -1;

			if (t0 > epsilon)
				t = t0;
			else if (t1 > epsilon)
				t = t1;
			else
				return false;

			intersect = ray.getDistanceT(t); 
			return true;
		}

	private:

};

/*
	Don't try to render planes, I didn't get it to work on time
*/
class Plane:public Shape {
	public :
		Vector normal;
		double distance;
		std::string name = "Plane";

		Plane(Vector norm, Vector org,double distance){
			normal = norm;
			origin = org;
			this->distance = distance;
		}

		Plane() {
			normal = Vector(0,1,0);
			Vector(0,0,0);
			distance = 10;
			mat = new Rubber();

		}

		inline bool intersect(Ray& ray, Vector& ri, Vector& normal, double& tclose, double& tfar, Shape*& hit, Shape*& curObj) {
			ray.getDirection().normalizeVector();
			

			 double PnRd = dotVectors(this->normal,ray.getDirection());
			 //std::cout << "PnRd: " << PnRd << std::endl;

			 if (PnRd >=0) {
				 return false;

			 }


			 Vector Ro = ray.getOrigin();
			 Ro.normalizeVector();
			 double t = -1*(dotVectors(this->normal, Ro) + this->distance)/ PnRd;


			 if (t<0 || t>tfar) 
				 return false;

			 ray.getDirection().normalizeVector();
			 Vector r = ray.getDirection();
			 Vector o = ray.getOrigin();
				
			 ri = Vector((o.x + (r.x*t)),(o.y+(r.y*t)),(o.z+(r.z*t)));
			 //normal = subPointsV( addPoints(ri,(0,5,0)),ri);
			 normal = this->normal;
			 normal.normalizeVector();



				return true;
		}

		virtual	inline bool intersect(Ray& ray, Vector interesect,double tfar) {

			return false;
		}

};

class Triangle:Shape {
	public :
			


	private:

};


