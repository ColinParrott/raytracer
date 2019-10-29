/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include <utility>

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

        float getReflectivity() const {
            return reflectivity;
        }

        const std::string &getTexturePath() const {
            return texturePath;
        }

        float getRefractiveIndex() const {
            return refractive_index;
        }

        float getTransparency() const {
            return transparency;
        }

        BlinnPhong(float kd, float ks, int specularExponent, float reflectivity, const Vec3f &diffuseColour,
                   float refractive_index, float transparency, std::string texturePath) : kd(kd),
                                                                      ks(ks),
                                                                      specularExponent(
                                                                              specularExponent),
                                                                      reflectivity(
                                                                              reflectivity),
                                                                      diffuseColour(
                                                                              diffuseColour),
                                                                      refractive_index(refractive_index),
                                                                      transparency(transparency),
                                                                      texturePath(std::move(texturePath)) {}

    private:
        float kd = 0.0f;
        float ks = 0.0f;
        int specularExponent = 0;
        float reflectivity = 0.0f;
        Vec3f diffuseColour;
        float refractive_index;
        float transparency;
        std::string texturePath;

    };


} //namespace rt



#endif /* BLINNPHONG_H_ */
