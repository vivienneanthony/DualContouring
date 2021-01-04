// Vivienne Anthony
// 2021

#ifndef MESHDATA_H
#define MESHDATA_H

#include <vector>

#include "../Util/Vect3.h"

// Shape Type
enum Shape
{
    Sphere,
    Terrain
};

// Basic class to create mesh data
class MeshData
{
public:
    MeshData();
    virtual ~MeshData();

    // Creat Mesh Data
    void CreateMeshData(Shape inshape);

   std::vector<PointV3> GetData();

protected:
private:
    std::vector<PointV3>  * randomPoints = nullptr;

};

#endif // MESHDATA_H
