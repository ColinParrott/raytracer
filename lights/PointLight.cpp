/*
 * PointLight.cpp
 *
 *
 */
#include "PointLight.h"


namespace rt {


    PointLight::PointLight(const Vec3f &position, const Vec3f &intensity, const Vec3f &colour) {
        this->position = position;
        this->intensity = intensity;
        this->colour = colour;
    }
} //namespace rt
