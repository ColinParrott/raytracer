/*
 * LightSource.cpp
 *
 */
#include "LightSource.h"

namespace rt{


    LightSource::LightSource(const Vec3f &position, const Vec3f &diffuseIntensity, const Vec3f &specIntensity, const Vec3f &colour) : position(position),
                                                                              diffuseIntensity(diffuseIntensity), specIntensity(specIntensity), colour(colour) {}

    LightSource::LightSource() = default;
} //namespace rt

