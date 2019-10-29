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

        Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Material *m) : v0(v0), v1(v1), v2(v2){
            this->material = m;
        };

        ~Triangle() override {
            delete material;
        }

        Hit intersect(Ray ray) override;


        const Vec3f &getV0() const;

        const Vec3f &getV1() const;

        const Vec3f &getV2() const;

    private:
        Vec3f v0;
        Vec3f v1;
        Vec3f v2;
    };


} //namespace rt




#endif /* TRIANGLE_H_ */
