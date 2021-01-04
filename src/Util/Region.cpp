// Vivienne Anthony
// 2021

#include <cmath>

#include "Region.h"

Region::Region()
{

}

// Constructor
Region::Region(Vect3 inMin, Vect3 inMax): Min(inMin), Max(inMax)
{

}

// Constructor
void Region::SetRegion(Vect3 inMin, Vect3 inMax)
{
    Min = inMin;
    Max = inMax;

}

Region::~Region()
{

}

// Calculate Center
Vect3 Region::CalculateCenter()
{
    return (Max+Min)/2.0f;
}

Vect3 Region::CalculateDimensions()
{
    // return absolute of each point
    return Vect3(std::abs(Max.x-Min.x),std::abs(Max.y-Min.y),std::abs(Max.z-Min.z));
}

bool Region::InRegion(Vect3 checkVect3)
{
    if(checkVect3.x>=Min.x&&
            checkVect3.y>=Min.y&&
            checkVect3.z>=Min.z&&
            checkVect3.x<=Max.x&&
            checkVect3.y<=Max.y&&
            checkVect3.z<=Max.z)
    {
        return true;
    }

    return false;
}
