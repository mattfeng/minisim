#ifndef ATOM_H
#define ATOM_H

#include "vec.h"
#include <string>

namespace Atom {
    enum Element {
        H = 1,
        He = 2,
        Li = 3,
        Be = 4,
        B = 5,
        C = 6,
        N = 7,
        O = 8,
        F = 9,
        Ne = 10,
        Na = 11,
        Mg = 12,
        Al = 13,
        Si = 14,
        P = 15,
        S = 16,
        Cl = 17,
        Ar = 18,
        K = 19,
        Ca = 20
    };

    const std::string element_names[] = {
        "!DUMMY",
        "Hydrogen",
        "Helium",
        "Lithium",
        "Beryllium",
        "Boron",
        "Carbon",
        "Nitrogen",
        "Oxygen",
        "Flourine",
        "Neon",
        "Sodium",
        "Magnesium",
        "Aluminium",
        "Silicon",
        "Phosphorus",
        "Sulfur",
        "Chlorine",
        "Argon",
        "Potassium",
        "Calcium"
    };
    
    class Atom {
    private:
        Element element;
        Vec3d position;

    public:
        Atom(Element e, Vec3d pos) : element(e), position(pos) {};
        std::string repr();
    };
}

#endif
