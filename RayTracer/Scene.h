#pragma once
#include"shape.h"
#include"vector.h"
#include"point.h"
#include<vector>
#include"lights.h"
#include <cmath>
#include<algorithm>

/*
	A scene has a list of lighets and shapes, are rendered in the ray tracer
*/

class Scene {
public:
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
				hitSomething = true;
			}


		}

		if (hitSomething)
			return true;

		return false;

	}
	

/*
This method is used for phong shading, gets ambient, diffuse, and specular lighting intensity
*/
	inline double getLightIntensity(Shape* &hit, Point hitPoint, Vector normal, Ray& rayI) {
		double Iamb = 0;
		double Idiff = 0;
		double Ispec = 0;
		bool lightMe = true; // if false, shadow is present
		double epsilon = 0.0001;
		rayI.getDirection().normalizeVector();

		//ambient, difuse and specular light calculated for each light in the scene 
		for (int i = 0; i < lights.size(); i++) {
			lightMe = true;
			Vector ray = subPointsV(lights[i].position,hitPoint);
			ray.normalizeVector();


			//abmient light

			Iamb += (ambI * hit->mat->ambR);

			// shadow

			for (int j = 0; j < objects.size(); j++) {
				Vector lightDist = subPointsV(lights[i].position,hitPoint);
				double lightD = lightDist.magnitude();

	
				Ray shadowRay = Ray(ray, addPoints(hitPoint,epsilon));
				shadowRay.getDirection().normalizeVector();
				Point inter = Point();

				if (objects[j]->intersect(shadowRay, inter)) {

					Vector vecDist = subPointsV(lights[i].position,inter);
					double dist = vecDist.magnitude();
					if (dist < lightD) {
						lightMe = false;
						break;
					}
				}
				
			}

			if (!lightMe)
				continue;


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





			}



			return (Iamb + Idiff + Ispec)/lights.size(); //avg the intensity for each light soruce

		}





};
