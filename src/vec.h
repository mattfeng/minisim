//#ifndef VEC_GUARD_H
//#define VEC_GUARD_H

#include <string>

struct Vec3d {
    double x;
    double y;
    double z;

    std::string repr(void);
};

double dist(Vec3d a, Vec3d b);

//#endif
