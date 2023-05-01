#pragma once
#include"shape.h"
#include"vector.h"
#include"point.h"
#include<vector>
#include"lights.h"
#include <cmath>
#include<algorithm>

class Scene {
public:
	//std::cout << "theta: " << cosTheta << std::endl<<std::endl;
	std::vector<Shape*> objects;
	std::vector<Light> lights;
	double ambI;

	Scene() : ambI(1) {}

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

	inline bool intersect(Ray& ray, Point& rayInt, Vector& rayNorm, double& tclose, double& tfar, Shape*& hitObject) {
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
	
	inline bool intesectsScene(Ray r) {
		double tfar=std::numeric_limits<double>::max();
		double tclose=std::numeric_limits<double>::max();

		for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->quickIntersect(r,tclose,tfar))
				return true;

		}

	}


	inline double getLightIntensity(Shape*& hit, Point hitPoint, Vector normal, Ray& rayI) {
		double Iamb = 0;
		double Idiff = 0;
		double Ispec = 0;
		double tfar=std::numeric_limits<double>::max();
		rayI.getDirection().normalizeVector();



		for (int i = 0; i < lights.size(); i++) {
			Vector ray = subPointsV(lights[i].position,hitPoint);
			ray.normalizeVector();


			//abmient light

			Iamb += (ambI * hit->mat->ambR);

			// shadow
/*

			for (int j = 0; j < objects.size(); j++) {
				double tclose = tfar;
				Ray shadowRay = Ray(ray, addPoints(hitPoint,0.1));
				shadowRay.getDirection().normalizeVector();

				if (objects[j]->quickIntersect(shadowRay,tclose,tfar)) 
					continue;
				
			}

*/
			
			
			
		
		
			
		

				//diffuse light
				normal.normalizeVector();
				double specAngle = (double)dotVectors(ray, normal);

				Idiff += (lights[i].intensity * std::max((double)specAngle, (double)0.0)) * hit->mat->diffR;

				//specular  light

				Vector negRay = multVectors(ray, -1);
				
				Vector reflection = getRefelction(negRay,normal);
				reflection.normalizeVector();

				Vector negIncident = multVectors(rayI.getDirection(),-1);
				negIncident.normalizeVector();

				double cosBeta = std::max(dotVectors(reflection,negIncident),0.0);


				Ispec += lights[i].intensity * (hit->mat->specR) * pow(cosBeta, hit->mat->specH);

				//			std::cout << "Iamb: " << Iamb <<" Idiff: "<< Idiff <<" Ispec: "<< Ispec << std::endl;




			}



			return (Iamb + Idiff + Ispec)/lights.size();

		}





};
