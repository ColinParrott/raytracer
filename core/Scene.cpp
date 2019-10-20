/*
 * Scene.cpp
 *
 */
#include <shapes/Sphere.h>
#include <lights/PointLight.h>
#include <lights/AreaLight.h>
#include <materials/BlinnPhong.h>
#include <shapes/Plane.h>
#include "Scene.h"


namespace rt {

/**
 * Parses json scene object to generate scene to render
 *
 * @param scenespecs the json scene specificatioon
 */
    void Scene::createScene(Value &scenespecs) {

        //----------parse json object to populate scene-----------
//	auto centre = Vec3f(0.0f, 0.0f, -1.0f);
//	float r = 0.5f;
//	auto *sphere = new Sphere(centre, r);
//	shapes.push_back(sphere);


        if (scenespecs.HasMember("backgroundcolor")) {
            populateVector3(scenespecs["backgroundcolor"], backgroundColour);
        }

        if(scenespecs.HasMember("ambient")){
            populateVector3(scenespecs["ambient"], ambient);
        }

        if (scenespecs.HasMember("lightsources")) {
            Value &lightsources = scenespecs["lightsources"];
            assert(lightsources.IsArray());
            populateLightSources(lightsources);
        }

        if (scenespecs.HasMember("shapes")){
            Value& shapes = scenespecs["shapes"];
            assert(shapes.IsArray());
            populateShapes(shapes);
        }
    }

    Hit Scene::intersect(Ray ray){
        Hit hit;
        hit.collided = false;
        double hitDistance = INFINITY;
        for (Shape *s : shapes) {
            Hit h = s->intersect(Ray(ray.originPoint, ray.direction, ray.rayType));

            // Get closest object that the ray hits
            if (h.collided) {
                double distance = (h.point - ray.originPoint).length();
                if (distance < hitDistance) {
                    hitDistance = distance;
                    hit = h;
                    hit.collided = true;
                }
            }
        }
        return hit;
    }

    Hit Scene::intersectIgnoreShape(Ray ray, Shape *shape){
        Hit hit;
        hit.collided = false;
        double hitDistance = INFINITY;
        for (Shape *s : shapes) {
            Hit h = s->intersect(Ray(ray.originPoint, ray.direction, ray.rayType));

            // Get closest object that the ray hits
            if (h.collided && s != shape) {
                double distance = (h.point - ray.originPoint).length();
                if (distance < hitDistance) {
                    hitDistance = distance;
                    hit = h;
                    hit.collided = true;
                }
            }
        }
        return hit;
    }

    void Scene::populateShapes(const Value &value){
        for(SizeType i = 0; i < value.Size(); i++){
            assert(value[i]["type"].IsString());
            std::string type = value[i]["type"].GetString();

            if(type == "sphere"){
                assertSphere(value[i]);
                Vec3f center = populateVector3(value[i]["center"]);
                float radius = value[i]["radius"].GetFloat();
                Material *material = this->populateMaterial(value[i]["material"]);
                auto *sphere = new Sphere(center, radius, material);
//                std::cout << sphere->toString() << std::endl;
                std::cout << ((BlinnPhong*) sphere->getMaterial())->getDiffuseColour() << std::endl;
                this->shapes.push_back(sphere);
                std::cout << ((BlinnPhong*)shapes[i]->getMaterial())->getDiffuseColour() << std::endl;
            }
            else if(type == "plane"){
                assertPlane(value[i]);
                Vec3f point = populateVector3(value[i]["point"]);
                Vec3f normal = populateVector3(value[i]["normal"]);
                Material *material = this->populateMaterial(value[i]["material"]);
                Plane *plane = new Plane(point, normal, material);
                this->shapes.push_back(plane);
            }
            else
            {
                std::cout << "[WARN] Not implemented parsing for shape: " << type << "\t" << "(IGNORING IT)" << std::endl;
            }
        }
    }

    Material* Scene::populateMaterial(const Value &material){
        float ks = material["ks"].GetFloat();
        float kd = material["kd"].GetFloat();
        int specularExponent = material["specularexponent"].GetFloat();
        Vec3f diffuseColour = populateVector3(material["diffusecolor"]);

        return new BlinnPhong(kd, ks, specularExponent, diffuseColour);
    }

    void Scene::assertPlane(const Value &plane){
        assert(plane.HasMember("point"));
        assert(plane.HasMember("normal"));
        assert(plane.HasMember("material"));
        assert(plane["point"].IsArray());
        assert(plane["normal"].IsArray());
        assert(plane["material"].IsObject());
        assertMaterial(plane["material"]);
    }

    void Scene::assertSphere(const Value &sphere){
        assert(sphere.HasMember("center"));
        assert(sphere.HasMember("radius"));
        assert(sphere.HasMember("material"));
        assert(sphere["center"].IsArray());
        assert(sphere["radius"].IsFloat());
        assert(sphere["material"].IsObject());
        assertMaterial(sphere["material"]);
    }

    void Scene::assertMaterial(const Value &material){
        assert(material.HasMember("ks"));
        assert(material.HasMember("kd"));
        assert(material.HasMember("specularexponent"));
        assert(material.HasMember("diffusecolor"));
        assert(material["ks"].IsFloat());
        assert(material["kd"].IsFloat());
        assert(material["specularexponent"].IsFloat());
        assert(material["diffusecolor"].IsArray());
    }

    void Scene::populateLightSources(const Value &value) {
        for (SizeType i = 0; i < value.Size(); i++) {
            assert(value[i]["type"].IsString());
            assert(value[i]["position"].IsArray());
            assert(value[i]["intensity"].IsArray());
            assert(value[i]["colour"].IsArray());
            std::string type = value[i]["type"].GetString();
            Vec3f pos = populateVector3(value[i]["position"]);
            Vec3f intensity = populateVector3(value[i]["intensity"]);
            Vec3f colour = populateVector3(value[i]["colour"]);

            LightSource *light;

            if (type == "pointlight") {
                light = new PointLight(pos, intensity, colour);
            } else if (type == "arealight") {
                light = new AreaLight(pos, intensity, colour);
            }
            else
            {
                std::cout << "[ERROR] UNKNOWN LIGHT TYPE: " << type << std::endl;
                std::cout << "Exiting!" << std::endl;
                exit(-1);
            }

            lightSources.push_back(light);
        }
    }

    void Scene::populateVector3(const Value &a, Vec3f &vec) {
        assert(a.IsArray());
        for (SizeType i = 0; i < a.Size(); i++) {
//            printf("a[%d] = %f\n", i, a[i].GetFloat());
            vec[i] = a[i].GetFloat();
        }
    }

    Vec3f Scene::populateVector3(const Value &a) {
        assert(a.IsArray());
        Vec3f temp = Vec3f();
        for (SizeType i = 0; i < a.Size(); i++) {
//            printf("a[%d] = %f\n", i, a[i].GetFloat());
            temp[i] = a[i].GetFloat();
        }

        return temp;
    }


}
//namespace rt
