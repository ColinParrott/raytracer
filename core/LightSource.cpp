/*
 * LightSource.cpp
 *
 */
#include "LightSource.h"

namespace rt{


    LightSource::LightSource(const Vec3f &position, const Vec3f &intensity) : position(position),
                                                                              intensity(intensity) {}

    LightSource::LightSource() = default;
} //namespace rt

