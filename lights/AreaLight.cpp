/*
 * AreaLight.cpp
 *
 *
 */
#include "AreaLight.h"




namespace rt{


    AreaLight::AreaLight(const Vec3f &position, const Vec3f &diffuseIntensity, const Vec3f &specIntensity, const Vec3f &colour) : LightSource(position, diffuseIntensity, specIntensity, colour) {

    }
} //namespace rt
