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

        Vec3f L = center - ray.origin;
        float tca = L.dotProduct(ray.direction);
        float d2 = L.dotProduct(L) - tca*tca;
        if (d2 > radius*radius) {
            h.collided = false;
            return h;
        }
        float thc = sqrtf(radius*radius - d2);
        float t0 = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0) t0 = t1;
        if (t0 < 1e-9){
            h.collided = false;
            return h;
        }

        h.collided = true;
        h.point = ray.origin + t0 * ray.direction;
        h.normal = getNormal(h.point);
        h.material = material;
        return h;

//        Vec3f l = this->center - ray.origin;
//        float adj = l.dotProduct(ray.direction);
//        float d2 = l.dotProduct(l) - (adj*adj);
//        float radius2 = this->radius * this->radius;
//
//        if (d2 > radius2){
//            h.collided = false;
//            return h;
//        }
//
//        float thc = std::sqrt(radius2 - d2);
//        float t0 = adj - thc;
//        float t1 = adj + thc;
//
//        float t;
//        if (t0 < 1e-9 && t1 < 1e-9){
//            h.collided = false;
//            return h;
//        }
//        else if(t0 < 1e-9){
//            t = t0;
//        }
//        else if(t1 < 1e-9){
//            t = t1;
//        }
//        else
//        {
//            t = (t0 < t1) ? t0 : t1;
//        }

//
//
//        h.collided = true;
//        h.point = ray.origin + t*ray.direction;
//        h.normal = getNormal(h.point);
//        h.material = material;
//        return h;

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


