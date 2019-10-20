/*
 * AreaLight.h
 *
 *
 */

#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "core/LightSource.h"

namespace rt{

class AreaLight:public LightSource{
public:
    AreaLight(const Vec3f &position, const Vec3f &diffuseIntensity, const Vec3f &specIntensity, const Vec3f &colour);
};



} //namespace rt




#endif /* AREALIGHT_H_ */
