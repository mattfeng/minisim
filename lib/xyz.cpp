/**
 * Reading XYZ coordinate files.
 * 
 */

#include <string>
#include <sstream>
#include <iostream>
#include <tuple>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>
#include "xyz.hpp"

using namespace std;

int Atom::nextId = 0;
map<int, Atom*> Atom::atom_list;
map<string, int> Atom::nextElementId;

const map<string, double> Atom::covalent_radius = {
  { "H", 0.37}, { "C", 0.77}, { "O", 0.73}, { "N", 0.75}, { "F", 0.71},
  { "P", 1.10}, { "S", 1.03}, {"Cl", 0.99}, {"Br", 1.14}, { "I", 1.33},
  {"He", 0.30}, {"Ne", 0.84}, {"Ar", 1.00}, {"Li", 1.02}, {"Be", 0.27},
  { "B", 0.88}, {"Na", 1.02}, {"Mg", 0.72}, {"Al", 1.30}, {"Si", 1.18},
  { "K", 1.38}, {"Ca", 1.00}, {"Sc", 0.75}, {"Ti", 0.86}, { "V", 0.79},
  {"Cr", 0.73}, {"Mn", 0.67}, {"Fe", 0.61}, {"Co", 0.64}, {"Ni", 0.55},
  {"Cu", 0.46}, {"Zn", 0.60}, {"Ga", 1.22}, {"Ge", 1.22}, {"As", 1.22},
  {"Se", 1.17}, {"Kr", 1.03}, { "X", 0.00}
};

string Atom::to_str() const {
  stringstream ss;
  ss << "Atom(";
  ss << "x=" << this->x << ", ";
  ss << "y=" << this->y << ", ";
  ss << "z=" << this->z;
  ss << ")";

  return ss.str();
}

string Molecule::to_str() const {
  stringstream ss;

  ss << "Molecule(\n";
  for (Atom atom: this->atoms) {
      ss << "  " << atom.to_str() << "\n";
  }
  ss << ")";
  ss << endl;

  return ss.str();
}

void Molecule::add_atom(Atom a) {
  this->atoms.push_back(a);
}

void Molecule::set_atom_count(int num_atoms) {
  this->atom_count = num_atoms;
}

void Molecule::set_comment(string comment) {
  this->comment = comment;
}

double Atom::distance_between(const Atom &a, const Atom &b) {
  double x1, y1, z1, x2, y2, z2;

  tie(x1, y1, z1) = a.position();
  tie(x2, y2, z2) = b.position();

  double dx = x2 - x1;
  double dy = y2 - y1;
  double dz = z2 - z1;

  return sqrt(dx * dx + dy * dy + dz * dz);
}

bool Atom::within_bonding_distance(const Atom &a, const Atom &b) {
  const double TOLERANCE = 1.2;

  double r1 = Atom::covalent_radius.at(a.elt);
  double r2 = Atom::covalent_radius.at(b.elt);

  return Atom::distance_between(a, b) < (TOLERANCE * (r1 + r2));
}

map<Atom, vector<Atom> > build_bond_graph(Molecule& m) {
  map<Atom, vector<Atom> > bonds;

  for (int i = 0; i < m.get_atoms().size(); i++) {
    for (int j = i + 1; j < m.get_atoms().size(); j++) {
      const Atom a1 = m.get_atoms()[i];
      const Atom a2 = m.get_atoms()[j];

      if (Atom::within_bonding_distance(a1, a2)) {
        bonds[a1].push_back(a2);
        bonds[a2].push_back(a1);
      }
    }
  }

  return bonds;
}

int read_xyz_file(Molecule& molecule, string fname) {
  ifstream fs(fname);

  if (!fs.is_open()) {
    return 1;
  }

  int num_atoms;
  string comment;

  fs >> num_atoms >> comment;
  fs.get();  // clear out the newline

  molecule.set_atom_count(num_atoms);
  molecule.set_comment(comment);

  string elt;
  double x, y, z;
  while ((fs >> elt >> x >> y >> z)) {
    molecule.add_atom(Atom(elt, x, y, z));
  }
  fs.close();

  return 0;
}