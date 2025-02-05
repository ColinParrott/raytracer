/*
 * Scene.h
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"

#include "core/LightSource.h"
#include "core/Shape.h"


using namespace rapidjson;

namespace rt{

class Scene {
public:

	Scene(){};

	~Scene(){
	    for(auto l : lightSources){
	        delete l;
	    }

	    for(auto s : shapes){
	        delete s;
	    }

	}

	void createScene(Value& scenespecs);
    Hit intersect(Ray ray);
    Hit intersectIgnoreShape(Ray ray, Shape *shape);
    std::vector<Shape*> shapes;
    Vec3f backgroundColour;
    Vec3f ambient;
    std::vector<LightSource*> lightSources;
private:



    void populateVector3(const Value &a, Vec3f &vec);

    void populateLightSources(const Value &value);

    Vec3f populateVector3(const Value &a);

    void populateShapes(const Value &value);

    void assertSphere(const Value &sphere);

    void assertMaterial(const Value &material);

    Material * populateMaterial(const Value &material);

    void assertPlane(const Value &plane);


    void assertTriangle(const Value &triangle);
};

} //namespace rt



#endif /* SCENE_H_ */
