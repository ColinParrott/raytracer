/*
 * PointLight.cpp
 *
 *
 */
#include "PointLight.h"



namespace rt{


    PointLight::PointLight(const Vec3f &position, const Vec3f &intensity){
        this->position = position;
        this->intensity = intensity;
    }
} //namespace rt
