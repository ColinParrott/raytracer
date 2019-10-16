/*
 * Sphere.h
 *
 *
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include <sstream>
#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"

namespace rt{

    class Sphere:public Shape{

    public:

        //
        // Constructors
        //
        Sphere();
        Sphere(const Vec3f &center, float radius, Material *material):center(center), radius(radius){
            this->material = material;
        };

        ~Sphere() override;


        std::string toString() const{
            std::stringstream result;
            result << "Sphere(c=" << center << ",r=" << radius << ")";
            return result.str();
        }

        //
        // Functions that need to be implemented, since Sphere is a subclass of Shape
        //
        Hit intersect(Ray ray);


        float radius;
    private:

        Vec3f center;

        Vec3f getNormal(Vec3f point);
    };



} //namespace rt




#endif /* SPHERE_H_ */
