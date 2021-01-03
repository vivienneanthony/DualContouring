
#include <vector>

#include "../Util/Vect3.h"
#include "../Util/Region.h"

// Quadrant class
enum class Octant : unsigned char
{
    Quadrant0 = 0x01,
    Quadrant1 = 0x02,
    Quadrant2 = 0x04,
    Quadrant3 = 0x08,
    Quadrant4 = 0x10,
    Quadrant5 = 0x20,
    Quadrant6 = 0x40,
    Quadrant7 = 0x80
};


#define OCTANTS 8
#define INITIALBOUND    512
#define LODDEPTH      8



// Child for a octree
class OctreeNode
{
public:
    // General constructor and deconstuctor
    OctreeNode();
    OctreeNode(Vect3 inMax);

    ~OctreeNode();

    // Boundary min and maximum
    Region BoundRegion;

    // Parent Node
    OctreeNode * Parent = nullptr;

    // Octant quadrant
    OctreeNode * Node[OCTANTS]; // Pointers for each octant

    // depth preset
    unsigned int depth = 0;

    // Points in a vector
    std::vector<PointV3>  * PointList;

    unsigned char activeOctants;

    bool hasChildren = false;

    bool treeReady = false;                             // tree ready

    void BuildTree(unsigned int indepth);               // build blank tree with no points

    void CalculateBounds(Octant octant);

    void PrintAll();
};
