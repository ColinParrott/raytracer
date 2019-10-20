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

        Vec3f l = this->center - ray.origin;
        float adj = l.dotProduct(ray.direction);
        float d2 = l.dotProduct(l) - (adj*adj);
        float radius2 = this->radius * this->radius;

        if (d2 > radius2){
            h.collided = false;
            return h;
        }

        float thc = std::sqrt(radius2 - d2);
        float t0 = adj - thc;
        float t1 = adj + thc;

        if (t0 < 1e-4 && t1 < 1e-4){
            h.collided = false;
            return h;
        }

        float t = (t0 < t1) ? t0 : t1;

        h.collided = true;
        h.point = ray.origin + t*ray.direction;
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


