/*
 * RayTracer.cpp
 *
 */
#include <shapes/Sphere.h>
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

        Vec3f *pixelbuffer = new Vec3f[camera->getWidth() * camera->getHeight()], *pixel = pixelbuffer;

        float fov_radians = camera->getFov() * (M_PI / 180);
        for(unsigned y = 0; y < camera->getHeight(); y++){
            for(unsigned x = 0; x < camera->getWidth(); x++, pixel++){
                float dirX = (x + 0.5) - camera->getWidth() / 2;
                float dirY = -(y + 0.5) + camera->getHeight() / 2;
                float dirZ = -camera->getHeight()/(2.0f*tan(fov_radians/2.0f));
                pixelbuffer[x+y*camera->getWidth()] = RayTracer::castRay(Vec3f(0, 0, 0), Vec3f(dirX, dirY, dirZ).normalize(), scene, nbounces);
            }
        }

        return pixelbuffer;
    }

    Vec3f RayTracer::castRay(const Vec3f &origin, const Vec3f &dir, Scene *scene, int nbounces){
        for(Shape *shape : scene->shapes){
            Hit h = shape->intersect(Ray(origin, dir, PRIMARY));
            if(h.collided){
                float facingRatio = std::max(0.0f, h.pointNormal.dotProduct(dir));
//                std::cout << facingRatio << std::endl;
                return shape->getMaterial()->getDiffuseColour() * facingRatio;
            }
            else
            {
                return scene->backgroundColour;
            }
        }
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
//            std::cout << *pixel << std::endl;
        }


        return pixelbuffer;

    }


} //namespace rt


