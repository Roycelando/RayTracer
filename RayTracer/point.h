#pragma once

class Point {
	public:

		double x, y, z;
		Point():x(0),y(0),z(0){
		}
		Point(double x, double y, double z) {
			this->x = x; 
			this->y = y; 
			this->z = z;
				
		}



};

	Point addPoints(Point a, Point b) {
		 return Point(a.x+b.x, a.y+b.y, a.z+b.z);

	}

	Point subPoints(Point a, Point b) {
		 return Point(a.x-b.x, a.y-b.y, a.z-b.z);

	}
