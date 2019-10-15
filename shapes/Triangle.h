/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "core/Shape.h"

namespace rt {

    class Triangle : public Shape {
    public:
        ~Triangle() override;

        Hit intersect(Ray ray) override;


    private:
        Vec3f vertices[3];
    };


} //namespace rt




#endif /* TRIANGLE_H_ */
