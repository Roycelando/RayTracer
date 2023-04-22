#pragma once
#include"vector.h"
#include"point.h"

class Shape {
	public:
		Point origin;
		Vector normal;
		
		Shape() {
			origin = Point();
			normal = Vector();
		}

		Shape() {
			origin = Point();
			normal = Vector();
		}

		virtual bool intersect() {
			return false;
		}
	private:

};


class Sphere:Shape {
	public :
		bool intersect() override{


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


