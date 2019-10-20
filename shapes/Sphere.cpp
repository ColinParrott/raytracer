/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"

#include <cmath>


namespace rt {

    Sphere::Sphere() {

    }

    Sphere::~Sphere() {
        delete material;
    }

    /**
     * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
     *
     * @param ray cast ray to check for intersection with shape
     *
     * @return hit struct containing intersection information
     *
     */
    Hit Sphere::intersect(Ray ray) {

        Hit h;
        //-----------to be implemented -------------
		Vec3f o = ray.originPoint;
		Vec3f d = ray.direction.normalize();
		Vec3f v = o - center;

		const float b = 2 * v.dotProduct(d);
		const float c = v.dotProduct(v) - (radius*radius);
		float delta = b*b - 4 * c;

		if (delta < 1e-4){
		    h.collided = false;
            return h;
		}

		const float t1 = (-b - std::sqrt(delta))/2;
		const float t2 = (-b + std::sqrt(delta))/2;

		float t = (t1 < t2) ? t1 : t2;

        h.collided = true;
        h.point = ray.originPoint + t * ray.direction;
        h.normal = getNormal(h.point);
        h.material = material;
        return h;
    }

    /**
     * Computes the normal vector to a sphere at a given point
     * @param point Point on sphere to calculate normal for
     * @return The normal vector for the given point
     */
    Vec3f Sphere::getNormal(Vec3f point) {
        return (point - center).normalize();
    }


} //namespace rt


