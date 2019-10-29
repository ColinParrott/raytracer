/*
 * TriMesh.h
 *
 *
 */

#ifndef TRIMESH_H_
#define TRIMESH_H_

#include <vector>
#include "core/Shape.h"
#include "Triangle.h"

namespace rt{

class TriMesh: public Shape{


public:

private:
    std::vector<Triangle> triangles;

};



} //namespace rt




#endif /* TRIMESH_H_ */
