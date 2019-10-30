/*
 * main.cpp
 *
 */

#include <iostream>
#include <fstream>
#include <shapes/Sphere.h>
#include <materials/BlinnPhong.h>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "math/geometry.h"
#include "parsers/PPMWriter.h"
#include "typeinfo"

#include "core/RayTracer.h"
#include "core/Camera.h"
#include "core/Scene.h"


using namespace rt;
using namespace rapidjson;

int main(int argc, char* argv[]){

    const bool DEBUG = true;

	//parse commandline arguments
	char* inputFile=argv[1];    //first command line argument holds the path to the json input file
	char* outputFile=argv[2];   //second command line argument holds the path to the output image file

	std::printf("Input file: %s\n",inputFile);

	//parse json input file using rapidjson
	std::ifstream ifs(inputFile);
	IStreamWrapper is(ifs);
	Document d;     // d holds the complete json object
	d.ParseStream(is);

	//generate a camera according to the input file
	Camera* camera=Camera::createCamera(d["camera"]);

	//print camera data (based on the input file provided)
	camera->printCamera();

	//generate the scene according to the input file
	Scene* scene=new Scene();
	scene->createScene(d["scene"]);


	if(DEBUG)
    {
        std::cout << "background colour: " << scene->backgroundColour << std::endl;
        std::cout << "num lights: " << scene->lightSources.size() << std::endl;
        std::cout << "num shapes: " << scene->shapes.size() << std::endl;

//        for(Shape *s : scene->shapes){
//            Sphere *sphere = (Sphere*) s;
//            std::cout << sphere->toString() << std::endl;
//            std::cout << ((BlinnPhong*)sphere->getMaterial())->getDiffuseColour() << std::endl;
//        }
    }


	//
	// Main function, render scene
	//
	Vec3f* pixelbuffer=RayTracer::render(camera, scene, d["nbounces"].GetInt());


	//convert linear RGB pixel values [0-1] to range 0-255
	RayTracer::tonemap(pixelbuffer, camera->getHeight() * camera->getWidth());


	std::printf("Output file: %s\n",outputFile);


	//write rendered scene to file (pixels RGB values must be in range 0255)
	PPMWriter::PPMWriter(camera->getWidth(), camera->getHeight(), pixelbuffer, outputFile);

    //free resources when rendering is finished
    delete camera;
    delete scene;
	delete pixelbuffer;
}


