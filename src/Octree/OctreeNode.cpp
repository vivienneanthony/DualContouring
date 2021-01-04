// Vivienne Anthony
// 2021

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

    //PointList = new std::vector<PointV3>();
}

OctreeNode::OctreeNode(Vect3 inMax)
{
    // copy bounds
    BoundRegion.Min = Vect3(0.0f,0.0f,0.0f);
    BoundRegion.Max = inMax;

    // set initial depth to zero
    depth = 0;

    //PointList = new std::vector<PointV3>();
}

OctreeNode::~OctreeNode()
{
    // loop through each
    for(unsigned i=0; i<OCTANTS; i++)
    {
        if(Node[i])
        {
            //  delete Node[i];
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


// Calculate Bounds
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

// Calculate Bounds
void OctreeNode::PreCalculateBounds(Octant octant, Vect3 &outMin, Vect3 &outMax)
{
    // this calculate the center of this this region
    Vect3 center = this -> BoundRegion.CalculateCenter();

    if ((Octant)octant == Octant::Quadrant0)
    {
        outMin = center;
        outMax = this->BoundRegion.Max;
    }
    else if ((Octant)octant == Octant::Quadrant1)
    {
        outMin = Vect3(this->BoundRegion.Min.x, center.y, center.z);
        outMax = Vect3(center.x, this->BoundRegion.Max.y, this->BoundRegion.Max.z);
    }
    else if ((Octant)octant == Octant::Quadrant2)
    {
        outMin = Vect3(this->BoundRegion.Min.x, this->BoundRegion.Min.y, center.z);
        outMax = Vect3(center.x, center.y, this->BoundRegion.Max.z);
    }
    else if ((Octant)octant == Octant::Quadrant3)
    {
        outMin = Vect3(center.x, this->BoundRegion.Min.y, center.z);
        outMax = Vect3(this->BoundRegion.Max.x, center.y, this->BoundRegion.Max.z);
    }
    else if ((Octant)octant == Octant::Quadrant4)
    {
        outMin = Vect3(center.x, center.y, this->BoundRegion.Min.z);
        outMax = Vect3(this->BoundRegion.Max.x, this->BoundRegion.Max.y, center.z);
    }
    else if ((Octant)octant == Octant::Quadrant5)
    {
        outMin = Vect3(this->BoundRegion.Min.x, center.y, this->BoundRegion.Min.z);
        outMax =  Vect3(center.x, this->BoundRegion.Max.y, center.z);
    }
    else if ((Octant)octant == Octant::Quadrant6)
    {
        outMin = this->BoundRegion.Min;
        outMax = center;

    }
    else if ((Octant)octant == Octant::Quadrant7)
    {
        outMin = Vect3(center.x, this->BoundRegion.Min.y, this->BoundRegion.Min.z);
        outMax =  Vect3(this->BoundRegion.Max.x, center.y, center.z);
    }

}


// Print All
void OctreeNode::PrintAll()
{
    if(treeReady)
    {
        std::cout << depth << " : Min (" << BoundRegion.Min.x << "," << BoundRegion.Min.y << "," << BoundRegion.Min.z << ")";
        std::cout << " Max (" << BoundRegion.Max.x << "," << BoundRegion.Max.y << "," << BoundRegion.Max.z << ")" << std::endl;

        if(hasChildren==false)
        {
            //std :: cout << "No Children" << std::endl;
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

// Print Depth of Octree
void OctreeNode::PrintDepth(unsigned int inDepth)
{
    if(treeReady)
    {
        if(inDepth==depth)
        {
            std::cout << "Min (" << BoundRegion.Min.x << "," << BoundRegion.Min.y << "," << BoundRegion.Min.z << ")";
            std::cout << " Max (" << BoundRegion.Max.x << "," << BoundRegion.Max.y << "," << BoundRegion.Max.z << ")" << std::endl;

            return;
        }

        if(hasChildren)
        {
            // loop through each
            for(unsigned i=0; i<OCTANTS; i++)
            {
                if(Node[i])
                {
                    Node[i]->PrintDepth(inDepth);
                }
            }
        }
    }

}

// Copy data from input
void OctreeNode::InitPointData(std::vector<PointV3> inData)
{
    // check if point list is created
    //PointList->clear();


    // copy data to root node
    while (inData.size())
    {
        PointListQueue.push(inData.back());

        inData.pop_back();
    }
}

void OctreeNode::BuildTreeFromData()
{
    // if tree not ready calculate bounds
    if(treeReady==false)
    {
        // loop through each
        for(unsigned i=0; i<OCTANTS; i++)
        {

            Node[i] = nullptr;
        }

        // if reached maxmimum depth close
        //if(depth>LODDEPTH)

        if(PointListQueue.size()<5||depth==LODDEPTH)
        {
            // loop through each
            while(PointListQueue.size())
            {
                PointV3 inVect = PointListQueue.front();
                PointList.push_back(inVect);

                PointListQueue.pop();
            }

            // set the maximum so set this node to ready
            hasChildren = false;
            treeReady = true;

            return;
        }

        // Create temporay regions
        Region TempRegions[8];

        // loop through each
        for(unsigned i=0; i<OCTANTS; i++)
        {
            Vect3 boundMin;
            Vect3 boundMax;

            // Calculate Bounds
            PreCalculateBounds((Octant)(1 << i), boundMin, boundMax);

            TempRegions[i].Min = boundMin;
            TempRegions[i].Max = boundMax;
        }


        bool inRegion = false;


        PointV3 inVect = PointListQueue.front();

        // this could possible sum each region and create 8 points average for each including the average name with a cutoff
        // idea so each depth progressively doubles the detail

        // loop through each
        while(PointListQueue.size())
        {

            for(unsigned i=0; i<OCTANTS; i++)
            {
                inRegion = TempRegions[i].InRegion(inVect.v);

                if(inRegion)
                {
                    if(Node[i])
                    {
                        Node[i]->AddQueue(inVect);

                    }
                    else
                    {
                        Node[i] = new OctreeNode();

                        // Populate node data
                        Node[i]-> Parent = this;
                        Node[i]-> depth = (depth+1);

                        // Calculate Bounds
                        Node[i]-> CalculateBounds((Octant)(1 << i));

                        // Activate this octant
                        States::activateIndex(&activeOctants, i);

                        // Add to quee
                        Node[i]->AddQueue(inVect);
                    }

                    break;
                }
            }

            // Pop first element
            PointListQueue.pop();

            inVect = PointListQueue.front();
        }

        // Build Tree
        for(unsigned int i=0; i<OCTANTS; i++)
        {
            // Calculate Bounds
            if(Node[i])
            {
                Node[i]->BuildTreeFromData();
            }
        }
    }
}


void OctreeNode::AddQueue(PointV3 inPoint)
{


    PointListQueue.push(inPoint);
}


void OctreeNode::PrintAllFromData()
{
    if(PointList.size())
    {
        unsigned int a = PointList.size();
        std::cout << " depth " << depth << " Points " << a << std::endl;
    }

    // loop through each
    for(unsigned int i=0; i<OCTANTS; i++)
    {
        // Calculate Bounds
        if(Node[i])
        {
            Node[i]->PrintAllFromData();
        }
    }

}
