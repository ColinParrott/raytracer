/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"
#include "Material.h"

namespace rt {

/*
 * Ray structure definition
 */
    enum RayType {
        PRIMARY, SECONDARY, SHADOW
    };

    struct Ray {

    public:

        Ray(const Vec3f &a, const Vec3f &b, RayType type) {
            originPoint = a;
            direction = b;
            rayType = type;
        }

        RayType rayType;
        Vec3f originPoint;
        Vec3f direction;

        //----------Ray variables to be filled------
    };

    struct Hit {

        Vec3f point; //point where ray hits a shape
        bool collided;
        //----------Hit variables to be filled------
    };


}


#endif /* CORE_RAYHITSTRUCTS_H_ */
