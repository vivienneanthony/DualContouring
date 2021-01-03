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

        // if depth is 0 then put invalid input
        if(inDepth==0)
        {
            std::cout << "Invalid Depth Input" << std::endl;

            return 0;
        }
    }


    OctreeNode * newTree = new OctreeNode(Vect3(1.0f,1.0f,1.0f));



    int BuildDepth = inDepth;

    newTree->BuildTree(BuildDepth);

    newTree->PrintDepth(BuildDepth);

    delete newTree;

    return 0;
}

