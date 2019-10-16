/*
 * Shape.cpp
 *
 */
#include "Shape.h"



namespace rt{


    Shape::Shape() = default;

    Shape::~Shape() = default;

    Material *Shape::getMaterial() const {
        return material;
    }
} //namespace rt

