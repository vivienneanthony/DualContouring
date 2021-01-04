#ifndef MESHDATA_H
#define MESHDATA_H

#include "src/Util/MeshData.h"

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
        CreateMeshData(Shape inshape);

    protected:
    private:

};

#endif // MESHDATA_H
