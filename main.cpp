#include <iostream>

#include "src/Octree/OctreeNode.h"


using namespace std;

int main()
{
    OctreeNode * newTree = new OctreeNode(Vect3(1.0f,1.0f,1.0f));

    int BuildDepth = 4;

    newTree->BuildTree(BuildDepth);

    newTree->PrintDepth(BuildDepth);

    delete newTree;

    return 0;
}
