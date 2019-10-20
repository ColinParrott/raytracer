/*
 * RayTracer.cpp
 *
 */
#include <shapes/Sphere.h>
#include <materials/BlinnPhong.h>
#include "RayTracer.h"


namespace rt {

    inline
    float deg2rad(const float &deg) { return deg * M_PI / 180; }


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
                                                                             nbounces);
            }
        }


        return pixelbuffer;
    }

    Vec3f RayTracer::castRay(const Vec3f &origin, const Vec3f &dir, Scene *scene, int nbounces) {

        Shape *hitObject;
        Vec3f hitPoint;
        Vec3f hitNormal;
        bool collided = false;
        double hitDistance = INFINITY;

        for (Shape *shape : scene->shapes) {
            Hit h = shape->intersect(Ray(origin, dir, PRIMARY));

            // Get closest object that the ray hits
            if (h.collided) {
                double distance =
                        pow(h.point.x - origin.x, 2) + pow(h.point.y - origin.y, 2) + pow(h.point.z - origin.z, 2);
                if (distance < hitDistance) {
                    hitObject = shape;
                    hitDistance = distance;
                    hitPoint = h.point;
                    hitNormal = h.pointNormal;
                    collided = true;
                }
            }
        }

        if (!collided)
            return scene->backgroundColour;

        BlinnPhong *mat = (BlinnPhong *) hitObject->getMaterial();


        // Add ambient light
        Vec3f iAmbient = scene->backgroundColour * mat->getDiffuseColour();
        Vec3f iDiffuse = Vec3f(0.0f, 0.0f, 0.0f);
        Vec3f iSpecular = Vec3f(0.0f, 0.0f, 0.0f);

        for (LightSource *lightSource : scene->lightSources) {

            // Add diffuse light
            Vec3f lightDir = (lightSource->position - hitPoint).normalize();
            Vec3f norm = hitNormal.normalize();

            float diffuseDot = lightDir.dotProduct(norm);
            if (diffuseDot > 0) {
                // Add diffuse
                iDiffuse = mat->getKd() * std::max(diffuseDot, 0.0f) * lightSource->intensity;

                // Add specular
                Vec3f viewDir = (origin - hitPoint).normalize();
                Vec3f reflectDir = RayTracer::getReflectionDirection(-lightDir, norm).normalize();
                float specDot = std::max(reflectDir.dotProduct(viewDir), 0.0f);
                iSpecular = mat->getKs() * std::pow(specDot, mat->getSpecularExponent()) * lightSource->intensity;

            }
        }
        return (iAmbient + iDiffuse + iSpecular) * mat->getDiffuseColour();
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

