/**
 * Geometry analysis of molecules.
 */

#define VERSION "0.0.1"

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "lib/xyz.hpp"

using namespace std;

void print_header() {
    stringstream title_str_ss;
    title_str_ss << "MINISIM (v" << VERSION << ")";
    string title_str = title_str_ss.str();
    cout << title_str << endl;
    cout << string(title_str.length(), '=') << "\n" << endl;
}

int main(int argc, char *argv[]) {
    print_header();

    Molecule m;
    read_xyz_file(m, "./molecules/benzene.xyz");

    map<Atom, vector<Atom> > bond_graph = build_bond_graph(m);

    map<Atom, vector<Atom> >::const_iterator it;
    for (it = bond_graph.begin(); it != bond_graph.end(); it++) {
        cout << it->first.element() << ": ";
        for (Atom atom: it->second) {
            cout << atom.element() << " ";
        }
        cout << endl;
    }
}