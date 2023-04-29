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

	Scene() : ambI(0.5) {}

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


	inline double getLightIntensity(Shape*& hit, Point hitPoint, Vector normal, Ray& rayI) {
		double Iamb = 0;
		double Idiff = 0;
		double Ispec = 0;
		double tfar=std::numeric_limits<double>::max();



		for (int i = 0; i < lights.size(); i++) {
			//diffuse light
			Vector ray = converToVector(subPoints(lights[i].position, hitPoint));
			ray.normalizeVector();
			Ray shadowRay = Ray(ray, hit->origin);

			for (int j = 0; j < objects.size(); j++) {
				if (objects[j]->quickIntersect(shadowRay, tfar)) {
					std::cout << "shadow ray time" << std::endl;
					continue;
				}

			//abmient light

			Iamb += (ambI * hit->mat->ambR);




				normal.normalizeVector();
				double cosTheta = (double)dotVectors(ray, normal);


				Idiff += (lights[i].intensity * std::max((double)cosTheta, (double)0.0)) * hit->mat->diffR;

				//specular  light

				Vector rayOpp = multVectors(ray, -1);
				rayOpp.normalizeVector();
				double cosThetaOpp = (double)dotVectors(rayOpp, normal);



				double val = 2 * cosThetaOpp;
				Vector vec = multVectors(normal, val);

				Vector reflect = subVectors(rayOpp, vec);
				reflect.normalizeVector();

				double cosBeta = dotVectors(reflect, rayI.getDirection());


				Ispec += lights[i].intensity * (hit->mat->specR) * pow(std::max(cosBeta, 0.0), hit->mat->specH);

				//			std::cout << "Iamb: " << Iamb <<" Idiff: "<< Idiff <<" Ispec: "<< Ispec << std::endl;




			}



			return Iamb + Idiff + Ispec;

		}





	}
};
