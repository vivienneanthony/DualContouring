#include <iostream>

#include "src/Octree/OctreeNode.h"
#include "src/MeshData/MeshData.h"

using namespace std;

int main(int argc, char *argv[])
{
    // preset a indepth
    unsigned int inDepth = 1;

    // check argument
    if(argc>1)
    {
        // convert char to number
        inDepth = (unsigned int) atoi(argv[1]);
    }

    // Create a tree
    OctreeNode * newTree = new OctreeNode(Vect3(1024.0f,1024.0f,1024.0f));


    MeshData newData;

    newData.CreateMeshData(Shape::Terrain);


    std::cout << "Get data" << std::endl;

    std::vector<PointV3> data = newData.GetData();

    std::cout << "Init point data" << std::endl;

    newTree->InitPointData(data);

    std::cout << "Build tree data" << std::endl;

    newTree->BuildTreeFromData();

    std::cout << "Print tree data" << std::endl;

    newTree->PrintAllFromData();

    // delete
    delete newTree;

    return 0;
}




    // set depth base on input
    //int BuildDepth = inDepth;

    // build tree
    //newTree->BuildTree(BuildDepth);

    // print results
    //newTree->PrintDepth(BuildDepth);
