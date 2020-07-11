#include "vec.h"
#include <sstream>
#include <stdio.h>
#include <cmath>
#include <string>

using namespace std;

string Vec3d::repr(void)
{
    char ret[128];
    sprintf(ret, "Vec3d[x=%.6f, y=%.6f, z=%.6f]", this->x, this->y, this->z);
    return string(ret);
}

double dist(Vec3d a, Vec3d b)
{
    return sqrtl((a.x - b.x) * (a.x - b.x) + 
                 (a.y - b.y) * (a.y - b.y) + 
                 (a.z - b.z) * (a.z - b.z));
}
