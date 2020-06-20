#ifndef XYZ_INCLUDE_GUARD
#define XYZ_INCLUDE_GUARD

#include <string>
#include <map>
#include <vector>
#include <tuple>

/**
 * Atoms are represented by XYZ coordinates in 3D
 * space, measured in angstroms.
 */
class Atom {
protected:
    static int nextId;
    static std::map<int, Atom*> atom_list;
private:
    const int id;
    const std::string elt;
    double x;
    double y;
    double z;
public:
    static const std::map<std::string, double> covalent_radius;
    static bool within_bonding_distance(const Atom &a, const Atom &b);
    static double distance_between(const Atom &a, const Atom &b);

    Atom(std::string elt, double x, double y, double z): id(nextId++), elt(elt), x(x), y(y), z(z) {
        atom_list[id] = this;
    }

    bool operator==(const Atom &b) const {
        return id == b.id;
    }

    bool operator!=(const Atom &b) const {
        return id != b.id;
    }

    bool operator<(const Atom &b) const {
        return id < b.id;
    }

    std::tuple<double, double, double> position() const {
        return std::tuple<double, double, double>(x, y, z);
    }

    std::string to_str() const;

    std::string element() const {
        return elt;
    }
};

/**
 * Molecules are represented as vectors of Atoms.
 */
class Molecule {
private:
    std::string comment;
    int atom_count;
    std::vector<Atom> atoms;
public:
    void add_atom(Atom);
    void set_atom_count(int);
    void set_comment(std::string);
    std::string to_str() const;
    const std::vector<Atom>& get_atoms() {
        return atoms;
    }
};

int read_xyz_file(Molecule&, std::string);
std::map<Atom, std::vector<Atom> > build_bond_graph(Molecule&);

#endif