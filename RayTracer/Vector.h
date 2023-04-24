#pragma once
#include<cmath>

class Vector {
	public:
		double x, y, z;

		Vector() {
			x = 0;
			y = 0;
			z = 0;
		}
		
		Vector(double x, double y, double z) {
			this->x = x;
			this->y = y;
			this->z = z;
			
		}


		inline void normalizeVector() {

			double mag = magnitude();

			x /= mag;
			y /= mag;
			z /= mag;

		}

		inline double magnitude() {
			double a = x * x;
			double b = y * y;
			double  c = z * z;

			return sqrt((a+b+c));
				

		}

		inline void printVector() {
			std::cout << "(" << x << " , " << y << " , " << z << ")" << std::endl;

		}


	private:


};


Vector addVectors(Vector a, Vector b) {

	return Vector((a.x+b.x),(a.y+b.y),(a.z+b.z));

}

Vector addVectors(Vector a, double b) {
	

	return Vector((a.x+b),(a.y+b),(a.z+b));

}

Vector subVectors(Vector a, Vector b) {

	return Vector((a.x-b.x),(a.y-b.y),(a.z-b.z));

}

Vector subVectors(Vector a, double b) {
	

	return Vector((a.x-b),(a.y-b),(a.z-b));

}


Vector multVectors(Vector a, Vector b) {

	return Vector((a.x*b.x),(a.y*b.y),(a.z*b.z));

}

Vector multVectors(Vector a, double b) {
	
	return Vector((a.x*b),(a.y*b),(a.z*b));

}

Vector crossVectors(Vector a, Vector b) {
	double s1 = (a.y * b.z) - (a.z * b.y);
	double s2 = (a.z*b.x) - (a.x*b.z);
	double s3 = (a.x*b.y - a.y*b.x);
	

	return Vector(s1, s2, s3);
}

double dotVectors(Vector a, Vector b) {

	return ((a.x*b.x) + (a.y*b.y) + (a.z*b.z));

}
