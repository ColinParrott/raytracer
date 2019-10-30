/*
 * RayTracer.cpp
 *
 */
#include <shapes/Sphere.h>
#include <materials/BlinnPhong.h>
#include "RayTracer.h"


namespace rt {

    /**
 * Performs ray tracing to render a photorealistic scene
 *
 * @param camera the camera viewing the scene
 * @param scene the scene to render, including objects and lightsources
 * @param nbounces the number of bounces to consider for raytracing
 *
 * @return a pixel buffer containing pixel values in linear RGB format
 */
    Vec3f *RayTracer::render(Camera *camera, Scene *scene, int nbounces) {

        Vec3f *pixelbuffer = new Vec3f[camera->getWidth() * camera->getHeight()];
        float fov_radians = camera->getFov() * (M_PI / 180);
        for (unsigned y = 0; y < camera->getHeight(); y++) {
            for (unsigned x = 0; x < camera->getWidth(); x++) {
                float dirX = (x + 0.5) - camera->getWidth() / 2;
                float dirY = -(y + 0.5) + camera->getHeight() / 2;
                float dirZ = -camera->getHeight() / (2.0f * tan(fov_radians / 2.0f));
                pixelbuffer[x + y * camera->getWidth()] = RayTracer::castRay(Vec3f(0, 0, 0),
                                                                             Vec3f(dirX, dirY, dirZ).normalize(), scene,
                                                                             nbounces, 0, PRIMARY);
            }
        }

        return pixelbuffer;
    }

    inline
    float clamp(const float &lo, const float &hi, const float &v)
    { return std::max(lo, std::min(hi, v)); }

    inline
    float fresnel(const Vec3f &I, const Vec3f &N, const float &ior)
    {
        float kr;
        float cosi = clamp(-1, 1, I.dotProduct(N));
        float etai = 1, etat = ior;
        if (cosi > 0) { std::swap(etai, etat); }
        // Compute sini using Snell's law
        float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
        // Total internal reflection
        if (sint >= 1) {
            kr = 1;
        }
        else {
            float cost = sqrtf(std::max(0.f, 1 - sint * sint));
            cosi = fabsf(cosi);
            float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
            float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
            kr = (Rs * Rs + Rp * Rp) / 2;
        }

        return kr;
    }

    Vec3f
    RayTracer::castRay(const Vec3f &origin, const Vec3f &dir, Scene *scene, int nbounces, int depth, RayType rayType) {

        // Return background colour if recursion depth is beyond limit
        if (depth > nbounces) {
            return scene->backgroundColour;
        }

        // Check if ray hits anything in scene
        Hit hit = scene->intersect(Ray(origin, dir, rayType));

        // Return background colour on miss
        if (!hit.collided)
            return scene->backgroundColour;

        auto *mat = (BlinnPhong *) hit.material;

        // Set ambient light
        Vec3f iAmbient = scene->backgroundColour * scene->ambient;

        Vec3f iDiffuse = Vec3f(0.0f, 0.0f, 0.0f);
        Vec3f iSpecular = Vec3f(0.0f, 0.0f, 0.0f);
        for (LightSource *lightSource : scene->lightSources) {

            Vec3f lightDir = (lightSource->position - hit.point).normalize();
            Vec3f norm = hit.normal;

            // Fix for shadow acne/self occlusion
            Vec3f shadowOrigin = lightDir.dotProduct(norm) < 0 ? hit.point - norm*1e-3 : hit.point + norm*1e-3;

            // If shadow ray hit an object, skip adding this light source's contribution to the final colour
            Hit shadowHit = scene->intersect(Ray(shadowOrigin, lightDir, SHADOW));
            if (shadowHit.collided && (shadowHit.point - shadowOrigin).norm() < (lightSource->position - hit.point).norm())
                continue;


            // Add diffuse and specular
            float diffuseDot = lightDir.dotProduct(norm);
            if (diffuseDot > 0) {
                // Add diffuse
                iDiffuse = mat->getKd() * std::max(diffuseDot, 0.0f) * lightSource->diffuseIntensity * mat->getDiffuseColour();

                // Add specular
                Vec3f viewDir = (origin - hit.point).normalize();
                Vec3f lightReflectDir = RayTracer::getReflectionDirection(-lightDir, norm).normalize();
                float specDot = std::max(lightReflectDir.dotProduct(viewDir), 0.0f);
                iSpecular = mat->getKs() * std::pow(specDot, mat->getSpecularExponent()) * lightSource->specIntensity *lightSource->colour;
            }

        }

        Vec3f reflectColour = Vec3f();
        Vec3f refractColour = Vec3f();

        if(mat->getReflectivity() > 0.01f){
            Vec3f reflectDir = RayTracer::getReflectionDirection(dir, hit.normal).normalize();
            Vec3f reflectOrig = reflectDir.dotProduct(hit.normal) < 0 ? hit.point - hit.normal*1e-3 : hit.point + hit.normal *1e-3;
            reflectColour = castRay(reflectOrig, reflectDir, scene, nbounces, depth + 1, SECONDARY);
        }

        if(mat->getTransparency() > 0.01f){
            Vec3f refractDir = RayTracer::getRefractionDirection(dir, hit.normal, mat->getRefractiveIndex(), 1.0f).normalize();
            Vec3f refractOrig = refractDir.dotProduct(hit.normal) < 0 ? hit.point - hit.normal*1e-3 : hit.point + hit.normal *1e-3;
            refractColour = castRay(refractOrig, refractDir, scene, nbounces, depth + 1, SECONDARY);
        }

        float kr = fresnel(dir, hit.normal, mat->getRefractiveIndex());
        return iAmbient + iDiffuse + iSpecular + (reflectColour * mat->getReflectivity() * kr) + (refractColour * mat->getTransparency() * (1-kr));
    }


    /**
 * Gets the reflection direction of a ray hit
 * @param lightDir Direction of light source (normalised)
 * @param hitNormal Normal of hit point (normalised)
 * @return Direction of reflection ray
 */
    Vec3f RayTracer::getReflectionDirection(const Vec3f &lightDir, const Vec3f &hitNormal) {
        return lightDir - (2.0f * lightDir.dotProduct(hitNormal) * hitNormal);
    }

    Vec3f RayTracer::getRefractionDirection(const Vec3f &I, const Vec3f &N, float eta_t, float eta_i=1.f){
        float cosi = - std::max(-1.f, std::min(1.f, I.dotProduct(N)));
        if (cosi<0){
            return RayTracer::getRefractionDirection(I, -N, eta_i, eta_t); // if the ray comes from the inside the object, swap the air and the media
        }
        float eta = eta_i / eta_t;
        float k = 1 - eta*eta*(1 - cosi*cosi);
        return k<0 ? Vec3f(1,0,0) : I*eta + N*(eta*cosi - sqrtf(k)); // k<0 = total reflection, no ray to refract. I refract it anyways, this has no physical meaning
    }

/**
 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
 *
 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
 *
 * @return the tonemapped image
 */
    Vec3f *RayTracer::tonemap(Vec3f *pixelbuffer, int size) {

        //---------tonemapping function to be filled--------

        Vec3f *pixel = pixelbuffer;
        float multiplier = 255.0f;
        for (int i = 0; i < size; ++i, ++pixel) {
            pixel->x *= multiplier;
            pixel->y *= multiplier;
            pixel->z *= multiplier;

            if (pixel->x > 255.0f) {
//                std::cout << "RBG OVERFLOW: " << pixel->x << std::endl;
                pixel->x = 255.0f;
            }
            if (pixel->y > 255.0f) {
//                std::cout << "RGB OVERFLOW: " << pixel->y << std::endl;
                pixel->y = 255.0f;
            }
            if (pixel->z > 255.0f) {
//                std::cout << "RGB OVERFLOW: " << pixel->z << std::endl;
                pixel->z = 255.0f;
            }
//            std::cout << *pixel << std::endl;
        }

        return pixelbuffer;

    } //namespace rt
}

