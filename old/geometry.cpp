/**
 * Geometry analysis of molecules.
 */
#define VERSION "0.0.1"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <map>
#include <unordered_set>
#include <tuple>
#include <array>
#include <vector>
#include "boost/functional/hash.hpp"
#include "lib/xyz.hpp"

using namespace std;

// Additional type definition for the bond graph of a molecule.
typedef map<Atom, vector<Atom> > bond_graph;

class BondAngle {

};

class BondStretch {
private:
  Atom a;
  Atom b;
public:
  BondStretch(Atom a, Atom b): a(a), b(b) {}

  bool operator==(const BondStretch &other) const {
    return ((a == other.a) && (b == other.b)) || ((a == other.b) && (b == other.a));
  }

  array<int, 2> getAtomIds() const {
    array<int, 2> s = {a.getId(), b.getId()};
    sort(s.begin(), s.end());
    return s;
  }

  string to_str() const {
    stringstream ss;
    ss << a.element() << a.getElementId() << "--" << b.element() << b.getElementId();
    return ss.str();
  }

  double compute_energy() const {
    a.

  }
};

class DihedralAngle {

};

namespace std {
  template <>
  struct hash<BondStretch> {
    size_t operator()(const BondStretch& bs) const {
      size_t seed = 0;
      array<int, 2> ids = bs.getAtomIds();
      boost::hash_combine(seed, ids[0]);
      boost::hash_combine(seed, ids[1]);

      return seed;
    }
  };
}

void print_header() {
  stringstream title_str_ss;
  title_str_ss << "MINISIM (v" << VERSION << ")";
  string title_str = title_str_ss.str();
  cout << title_str << endl;
  cout << string(title_str.length(), '=') << "\n" << endl;
}

/**
 * Get the bond stretch energy terms.
 */
unordered_set<BondStretch> get_bond_stretch_energies(const bond_graph& bg) {
  unordered_set<BondStretch> v;

  bond_graph::const_iterator it;
  for (it = bg.begin(); it != bg.end(); it++) {
    Atom a = it->first;
    for (Atom b: it->second) {
      BondStretch bs = BondStretch(a, b);
      v.insert(bs);
    }
  }

  return v;
}

int main(int argc, char *argv[]) {
  print_header();

  Molecule m;
  read_xyz_file(m, "./molecules/xyz/benzene.xyz");

  bond_graph bg = build_bond_graph(m);
  unordered_set<BondStretch> all_bond_stretch = get_bond_stretch_energies(bg);

  unordered_set<BondStretch>::const_iterator bsit;
  for (bsit = all_bond_stretch.begin(); bsit != all_bond_stretch.end(); bsit++) {
    cout << (*bsit).to_str() << endl;
  }

  return 0;
}