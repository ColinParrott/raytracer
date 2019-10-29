//
// Created by Colin on 20/10/2019.
//

#ifndef RAY_TRACER_PLANE_H
#define RAY_TRACER_PLANE_H


#include "core/Shape.h"

namespace rt {

    class Plane : public Shape {

    public:
        Plane(const Vec3f &point, const Vec3f &normal, Material *material): point(point), normal(normal){
            this->material = material;
        }

        ~Plane() override{
            delete material;
        }

        Hit intersect(Ray ray);


    private:
        Vec3f point;
        Vec3f normal;
    };


} //namespace rt

#endif //RAY_TRACER_PLANE_H
