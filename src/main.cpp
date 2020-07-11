/**
 *
 *
 *
 *
 *
 */

#include "atom.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    Atom::Atom a(Atom::H, {0.0, 0.0, 0.0});

    cout << a.repr() << endl;

    return 0;
}
