/*
 * Material.h
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <math/geometry.h>

namespace rt{

class Material{
public:

    Material(float kd, float ks, int specularExponent, const Vec3f &diffuseColour) : kd(kd), ks(ks),
                                                                                     specularExponent(specularExponent),
                                                                                     diffuseColour(diffuseColour) {}


private:
    float kd = 0.0f;
    float ks = 0.0f;
    int specularExponent = 0;
    Vec3f diffuseColour;
};


} //namespace rt



#endif /* MATERIAL_H_ */
