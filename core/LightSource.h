/*
 * LightSource.h
 *
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_


#include <math/geometry.h>

namespace rt{

class LightSource{
public:
    LightSource(const Vec3f &position, const Vec3f &diffuseIntensity, const Vec3f &specIntensity, const Vec3f &colour);

    LightSource();

public:

    Vec3f colour;
    Vec3f position;
    Vec3f diffuseIntensity;
    Vec3f specIntensity;
};


} //namespace rt



#endif /* LIGHTSOURCE_H_ */
