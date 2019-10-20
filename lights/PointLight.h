/*
 * PointLight.h
 *
 *
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "core/LightSource.h"


namespace rt{

class PointLight: public LightSource{


public:
    PointLight(const Vec3f &position, const Vec3f &intensity, const Vec3f &colour);
};



} //namespace rt




#endif /* POINTLIGHT_H_ */
