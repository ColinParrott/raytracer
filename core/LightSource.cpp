/*
 * LightSource.cpp
 *
 */
#include "LightSource.h"

namespace rt{


    LightSource::LightSource(const Vec3f &position, const Vec3f &intensity, const Vec3f &colour) : position(position),
                                                                              intensity(intensity), colour(colour) {}

    LightSource::LightSource() = default;
} //namespace rt

