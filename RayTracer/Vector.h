#pragma once
#include<cmath>
#include<optional>
#include<cmath>

/*
	Defines my vector and a bunch of useful operations
*/

class Vector {
	public:
		double x, y, z;

		Vector() :x(0), y(0),z(0) {}
		
		Vector(double x, double y, double z): x(x), y(y), z(z) {}


		inline void normalizeVector() {

			double mag = magnitude();

			x = x/ mag;
			y = y/ mag;
			z = z/mag;

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

 void printVector(Vector v) {
			std::cout << "(" << v.x << " , " << v.y << " , " << v.z << ")" << std::endl;

}

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


/*
Gets the reflection vector
*/
Vector getRefelction(Vector I, Vector n) {
	I.normalizeVector();
	n.normalizeVector();
	//std::cout << " mag: " << n.magnitude() << std::endl;

	double beta = 2 * dotVectors(I,n);

	Vector N = multVectors(n, beta);

	Vector R = subVectors(I, N);
	R.normalizeVector(); 

	return R;
}


Vector getRefraction( const Vector I,  const Vector N, const double etai, const double etat) {
	
	Vector T = Vector();
	Vector NegNormal = multVectors(N,-1);


	double ci = dotVectors(I, NegNormal);
	double eta = etai / etat; // snells law

	if (ci < 0) {
		eta = 1/eta;
		ci = -ci;
	}


	double etaPow = eta * eta;
	double ciPow = ci*ci;
	double k = 1 + etaPow * (ciPow-1);

	if (k>0) {
		double beta = (eta * ci) - (sqrt(k));
		Vector etaI = multVectors(I,eta);
		Vector betaN = multVectors(N,beta); // Normal vector
		T = addVectors(etaI,betaN); // Transmissin vector
		T.normalizeVector();
	}

		return T;

}


