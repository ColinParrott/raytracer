//
// Created by Colin on 20/10/2019.
//

#include "Plane.h"

namespace rt {


    Hit Plane::intersect(Ray ray) {

        // Help from: https://en.wikipedia.org/wiki/Line-plane_intersection
        Hit h;

        float denom = normal.dotProduct(ray.direction.normalize());

        if(std::fabs(denom) > 0.0001f){
            float t = (point - ray.originPoint).dotProduct(normal) / denom;

            if(t >= 1e-4){
                h.collided = true;
                h.point = ray.originPoint + t*ray.direction;
                h.normal = normal.normalize();
                h.material = material;
                return h;
            }
        }
        h.collided = false;
        return h;
    }

}