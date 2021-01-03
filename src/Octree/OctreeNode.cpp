#include <iostream>

#include "OctreeNode.h"

#include "../Util/Region.h"
#include "../Util/Vect3.h"
#include "../Util/States.hpp"

OctreeNode::OctreeNode()
{
    // Set default boungs to 1
    BoundRegion.Min = Vect3(0.0f,0.0f,0.0f);
    BoundRegion.Max = Vect3(1.0f,1.0f,1.0f);

    // set initial depth to zero
    depth = 0;
}

OctreeNode::OctreeNode(Vect3 inMax)
{
    // copy bounds
    BoundRegion.Min = Vect3(0.0f,0.0f,0.0f);
    BoundRegion.Max = inMax;

    // set initial depth to zero
    depth = 0;
}

OctreeNode::~OctreeNode()
{
    // loop through each
    for(unsigned i=0; i<OCTANTS; i++)
    {
        if(Node[i])
        {
            delete Node[i];
        }
    }

}

void OctreeNode::BuildTree(unsigned int indepth)
{
    // this says a node is not created yet
    if(treeReady == false)
    {

        // if reached maxmimum depth close
        if(depth>=indepth||depth>LODDEPTH)
        {
            // set the maximum so set this node to ready
            hasChildren = false;
            treeReady = true;

            return;
        }

        // loop through each
        for(unsigned i=0; i<OCTANTS; i++)
        {
            // Octant quadrant
            Node[i] = new OctreeNode();

            // Populate node data
            Node[i]-> Parent = this;
            Node[i]-> depth = (depth+1);

            // Calculate Bounds
            Node[i]-> CalculateBounds((Octant)(1 << i));

            // Activate this octant
            States::activateIndex(&activeOctants, i);

            // Build Treee
            Node[i] -> BuildTree(indepth);
        }
    }

    hasChildren = true;
    treeReady = true;

    return;
}


void OctreeNode::CalculateBounds(Octant octant)
{
    // this calculate the center of this parent region
    Vect3 center = Parent -> BoundRegion.CalculateCenter();

    if ((Octant)octant == Octant::Quadrant0)
    {
        BoundRegion.SetRegion(center, Parent->BoundRegion.Max);
    }
    else if ((Octant)octant == Octant::Quadrant1)
    {
        BoundRegion.SetRegion(Vect3(Parent->BoundRegion.Min.x, center.y, center.z), Vect3(center.x, Parent->BoundRegion.Max.y, Parent->BoundRegion.Max.z));
    }
    else if ((Octant)octant == Octant::Quadrant2)
    {
        BoundRegion.SetRegion(Vect3(Parent->BoundRegion.Min.x, Parent->BoundRegion.Min.y, center.z), Vect3(center.x, center.y, Parent->BoundRegion.Max.z));
    }
    else if ((Octant)octant == Octant::Quadrant3)
    {
        BoundRegion.SetRegion(Vect3(center.x, Parent->BoundRegion.Min.y, center.z), Vect3(Parent->BoundRegion.Max.x, center.y, Parent->BoundRegion.Max.z));
    }
    else if ((Octant)octant == Octant::Quadrant4)
    {
        BoundRegion.SetRegion(Vect3(center.x, center.y, Parent->BoundRegion.Min.z), Vect3(Parent->BoundRegion.Max.x, Parent->BoundRegion.Max.y, center.z));
    }
    else if ((Octant)octant == Octant::Quadrant5)
    {
        BoundRegion.SetRegion(Vect3(Parent->BoundRegion.Min.x, center.y, Parent->BoundRegion.Min.z), Vect3(center.x, Parent->BoundRegion.Max.y, center.z));
    }
    else if ((Octant)octant == Octant::Quadrant6)
    {
        BoundRegion.SetRegion(Parent->BoundRegion.Min, center);
    }
    else if ((Octant)octant == Octant::Quadrant7)
    {
        BoundRegion.SetRegion(Vect3(center.x, Parent->BoundRegion.Min.y, Parent->BoundRegion.Min.z), Vect3(Parent->BoundRegion.Max.x, center.y, center.z));
    }

}

void OctreeNode::PrintAll()
{
    if(treeReady)
    {
        std::cout << BoundRegion.Min.x << " " << BoundRegion.Min.y << " " << BoundRegion.Min.z << std::endl;
        std::cout << BoundRegion.Max.x << " " << BoundRegion.Max.y << " " << BoundRegion.Max.z << std::endl;

        if(hasChildren==false)
        {

            std :: cout << "No Children" << std::endl;

            return;
        }

        // loop through each
        for(unsigned i=0; i<OCTANTS; i++)
        {
            if(Node[i])
            {
                Node[i]->PrintAll();
            }
        }
    }

}
