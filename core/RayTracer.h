/*
 * RayTracer.h
 *
 */
#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "math/geometry.h"
#include "core/Camera.h"
#include "core/Scene.h"

namespace rt{



/*
 * Raytracer class declaration
 */
class RayTracer {
public:

	RayTracer();

	static Vec3f* render(Camera* camera, Scene* scene, int nbounces);
	static Vec3f* tonemap(Vec3f* pixelbuffer, int size);


private:

    static Vec3f castRay(const Vec3f &origin, const Vec3f &dir, Scene *scene, int nbounces, int depth, RayType rayType);

    static Vec3f getReflectionDirection(const Vec3f &lightDir, const Vec3f &hitNormal);

    static Vec3f getRefractionDirection(const Vec3f &I, const Vec3f &N, float eta_t, float eta_i);
};




} //namespace rt



#endif /* RAYTRACER_H_ */

