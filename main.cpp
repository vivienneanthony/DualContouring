#include <iostream>

#include "src/Octree/OctreeNode.h"


using namespace std;

int main()
{
    OctreeNode * newTree = new OctreeNode();

    newTree->BuildTree(2);

    newTree->PrintAll();

    delete newTree;

    return 0;
}
