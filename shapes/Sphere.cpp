/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"


namespace rt{

    Sphere::~Sphere() = default;

	/**
	 * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */
	Hit Sphere::intersect(Ray ray){

//	    std::cout << "intersect()" << std::endl;
		Hit h;
		//-----------to be implemented -------------

		Vec3f oc = ray.originPoint - this->center;
		float a = ray.direction.dotProduct(ray.direction);
		float b = 2.0f * ray.direction.dotProduct(oc);
		float c = oc.dotProduct(oc) - (this->radius * this->radius);

		float discriminant = b*b - 4*a*c;

		if(discriminant <= 0){
//		    std::cout << "hit!!" << std::endl;
		    h.collided = false;
		    h.point = NULL;
		    h.color = Vec3i(0,0,0);
		    return h;
		}
		else
        {
//		    std::cout << "miss!" << std::endl;
		    h.collided = true;
		    h.point = NULL; // todo: calculate!
		    h.color = Vec3i(255, 0, 0);
		    return h;
        }


	}

    Sphere::Sphere() {

    }

} //namespace rt


