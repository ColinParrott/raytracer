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


        auto origin = Vec3f(0.0, 0.0, 0.0);
        auto lowerLeftCorner = Vec3f(-2.0, -1.0, -1.0);
        auto horizontal = Vec3f(4.0, 0.0, 0.0);
        auto vertical = Vec3f(0.0, 2.0, 0.0);
        //----------main rendering function to be filled------
        for(unsigned y = 0; y < camera->getHeight(); ++y){
            for(unsigned x = 0; x < camera->getWidth(); ++x, ++pixel){
                float u = float(x) / float(camera->getWidth());
                float v = float(y) / float(camera->getHeight());
                Ray ray = Ray(origin, lowerLeftCorner + u*horizontal + v*vertical, PRIMARY);
                Shape *sphere = scene->shapes[0];
                std::cout << scene->backgroundColour << std::endl;
                if(sphere->intersect(ray).collided)
                    *pixel = Vec3f(255.0f, 0.0f, 0.0f);
                else
                    *pixel = Vec3f(0.0f, 255.0f, 0.0f);
            }
        }


       return pixelbuffer;
    }

/**
 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
 *
 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
 *
 * @return the tonemapped image
 */
    Vec3f *RayTracer::tonemap(Vec3f *pixelbuffer) {

        //---------tonemapping function to be filled--------





        return pixelbuffer;

    }


} //namespace rt


