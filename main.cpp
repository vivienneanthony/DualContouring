#include <iostream>

#include "src/Octree/OctreeNode.h"


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
    OctreeNode * newTree = new OctreeNode(Vect3(1.0f,1.0f,1.0f));

    // set depth base on input
    int BuildDepth = inDepth;

    // build tree
    newTree->BuildTree(BuildDepth);

    // print results
    newTree->PrintDepth(BuildDepth);

    // delete
    delete newTree;

    return 0;
}

