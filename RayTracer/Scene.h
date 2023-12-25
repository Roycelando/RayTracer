#pragma once
#include"shape.h"
#include"vector.h"
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

	inline bool intersect(Ray& ray, Vector& rayInt, Vector& normal, double& tclose, Shape* &hitObject) {
		bool hitSomething = false;
		for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->intersect(ray, rayInt, normal, tclose, hitObject, objects[i])) 
				hitSomething = true;

		}

		return hitSomething;

	}
	

/*
This method is used for phong shading, gets ambient, diffuse, and specular lighting intensity
*/
	inline double shade(Shape* &hitObj, Vector hitPoint, Vector& normal, Ray& rayI) {
		double Iamb = 0;
		double Idiff = 0;
		double Ispec = 0;
		bool lightMe = true; // if false, shadow is present
		double epsilon = 0.0001;
		rayI.getDirection().normalizeVector();

		//ambient, difuse and specular light calculated for each light in the scene 
		for (int i = 0; i < lights.size(); i++) {
			lightMe = true;
			Vector lightRay = subVectors(lights[i].position,hitPoint); // ray from hit point to light
			lightRay.normalizeVector();


			//abmient light
			hitObj->mat->refrac;

			Iamb += (ambI * hitObj->mat->ambR);

			// shadow 

			for (int j = 0; j < objects.size(); j++) {
				double lightDistance = lightRay.magnitude();
				Ray shadowRay = Ray(lightRay, addVectors(hitPoint,epsilon));
				shadowRay.getDirection().normalizeVector();
				Vector inter = Vector();

				if (objects[j]->intersect(shadowRay, inter)) {
					Vector vecDist = subVectors(lights[i].position,inter);
					double dist = vecDist.magnitude();

					if (dist < lightDistance) {
						lightMe = false;
						break;
					}
				}
				
			}

			if (!lightMe)
				continue;


				//diffuse light
				double diffuseAngle = std::max(dotVectors(lightRay, normal),0.0);

				Idiff += (lights[i].intensity * diffuseAngle* hitObj->mat->diffR);

				//specular  light

				Vector negLightRay = multVectors(lightRay, -1);
				Vector reflection = getRefelction(negLightRay,normal);
				Vector incedentRay = multVectors(rayI.getDirection(),-1);
				incedentRay.normalizeVector();
				double cosBeta = std::max(dotVectors(reflection, incedentRay), 0.0);

				Ispec += (lights[i].intensity * (hitObj->mat->specR) * pow(cosBeta, hitObj->mat->specH));

			}



			return (Iamb + Idiff + Ispec)/lights.size(); //avg the intensity for each light soruce

		}





};
