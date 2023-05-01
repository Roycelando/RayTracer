#pragma once

/*
	Defines point which are defined by x,y,z coordianates
*/

class Point {
	public:

		double x, y, z;
		Point():x(0),y(0),z(0){
		}
		Point(double x, double y, double z): x(x), y(y), z(z) {
						
		}



};
	Point multPoints(Point a, Point b) {
		 return Point((a.x*b.x), (a.y*b.y), (a.z*b.z));

	}
	Point addPoints(Point a, Point b) {
		 return Point((a.x+b.x), (a.y+b.y), (a.z+b.z));

	}
	Point addPoints(Point a, double b) {
		 return Point((a.x+b), (a.y+b), (a.z+b));

	}
	Point subPoints(Point a, Point b) {
		 return Point((a.x-b.x), (a.y-b.y), (a.z-b.z));

	}
