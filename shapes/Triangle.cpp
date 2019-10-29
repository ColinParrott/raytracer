/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"


namespace rt {


    Hit Triangle::intersect(Ray ray) {
        Hit h;

        // Moller-trumbore algorithm (https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf)

        float CUT_OFF = 1e-6;

        Vec3f edge1 = v1 - v0;
        Vec3f edge2 = v2 - v0;
        Vec3f j = ray.direction.crossProduct(edge2);
        float a = edge1.dotProduct(j);

        if(a > -CUT_OFF && a < CUT_OFF){
            h.collided = false;
            return h;
        }

        float f = 1.0f/a;
        Vec3f s = ray.origin - v0;
        float u = f * s.dotProduct(j);

        if(u < 0.0 || u > 1.0){
            h.collided = false;
            return h;
        }

        Vec3f q = s.crossProduct(edge1);
        float v = f * ray.direction.dotProduct(q);

        if(v < 0.0 || u + v > 1.0){
            h.collided = false;
            return h;
        }

        float t = f * edge2.dotProduct(q);

        if(t >  CUT_OFF && t < 1/CUT_OFF){
            h.collided = true;
            h.point = ray.origin + ray.direction * t;
            h.material = this->material;

            // Get normal by using two edges of triangle
            h.normal = edge2.crossProduct(edge1);
            return h;
        }
        else{
            h.collided = false;
            return h;
        }

    }

    const Vec3f &Triangle::getV0() const {
        return v0;
    }

    const Vec3f &Triangle::getV1() const {
        return v1;
    }

    const Vec3f &Triangle::getV2() const {
        return v2;
    }


} //namespace rt
