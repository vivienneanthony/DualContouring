#include <iostream>

#include "src/Octree/OctreeNode.h"


using namespace std;

int main()
{
    OctreeNode * newTree = new OctreeNode();
\
    newTree->BoundRegion.Max = Vect3(1024.0f,1024.0f,1024.0f);

    newTree->BuildTree(2);

    newTree->PrintAll();

    delete newTree;

    return 0;
}
