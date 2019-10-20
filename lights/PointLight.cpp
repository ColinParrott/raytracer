/*
 * PointLight.cpp
 *
 *
 */
#include "PointLight.h"


namespace rt {


    PointLight::PointLight(const Vec3f &position, const Vec3f &diffuseIntensity, const Vec3f &specIntensity, const Vec3f &colour) {
        this->position = position;
        this->diffuseIntensity = diffuseIntensity;
        this->specIntensity = specIntensity;
        this->colour = colour;
    }
} //namespace rt
