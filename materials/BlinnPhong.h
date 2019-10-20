/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include "core/Material.h"


namespace rt {

    class BlinnPhong : public Material {

    public:

        float getKd() const {
            return kd;
        }

        float getKs() const {
            return ks;
        }

        float getSpecularExponent() const {
            return specularExponent;
        }

        const Vec3f &getDiffuseColour() const {
            return diffuseColour;
        }

        BlinnPhong(float kd, float ks, float specularExponent, const Vec3f &diffuseColour) : kd(kd), ks(ks),
                                                                                           specularExponent(
                                                                                                   specularExponent),
                                                                                           diffuseColour(
                                                                                                   diffuseColour) {}

    private:
        float kd = 0.0f;
        float ks = 0.0f;
        float specularExponent = 0.0f;
        Vec3f diffuseColour;

    };


} //namespace rt



#endif /* BLINNPHONG_H_ */
