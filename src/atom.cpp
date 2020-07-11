#include "atom.h"
#include <sstream>
#include <string>

using namespace std;

namespace Atom {

    string Atom::repr()
    {
        ostringstream oss;

        oss << "Atom[" << element_names[this->element] << ", " << this->position.repr() << "]";

        return oss.str();
    }
}
