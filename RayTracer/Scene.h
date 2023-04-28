#pragma once
#include"shape.h"
#include"vector.h"
#include"point.h"
#include<vector>
#include"lights.h"

class Scene {
	public:
	std::vector<Shape*> objects;
	std::vector<Light> lights;
	double ambI;
	
		Scene(): ambI(1)  {}

		Scene(double ambi) : ambI(ambi) {}


	void addObjects(Shape* obj) {
		objects.push_back(obj);

	}

	void addLights(Light li) {
		lights.push_back(li);

	}
	std::vector<Shape*> getObjectList() {
		return objects;

	}

	std::vector<Light> getLightList() {
		return lights;

	}

	inline bool intersect(Ray& ray, Point& rayInt, Vector& rayNorm, double& tclose, double& tfar,Shape* & hitObject) {
		bool hitSomething = false;
		for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->intersect(ray, rayInt, rayNorm, tclose, tfar, hitObject, objects[i])) {
			//	std::cout << "for loop of intersection" << std::endl;
				hitSomething = true;
			}


		}

		if (hitSomething)
			return true;

		return false;

	}


	inline double getLightIntensity(Shape* & hit) {
		double Iamb = 0;
		double Idiff =0;
		double Ispec=0;

		for (int i = 0; i < lights.size(); i++) {
			Iamb += (ambI * hit->mat->ambR);
				

		}



		return Iamb+Idiff+Ispec;

	}

	



};

