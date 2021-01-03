#include "Region.h"

Region::Region()
{

}

Region::Region(Vect3 inMin, Vect3 inMax): Min(inMin), Max(inMax)
{

}

void Region::SetRegion(Vect3 inMin, Vect3 inMax)
{
    Min = inMin;
    Max = inMax;

}

Region::~Region()
{

}

// returns the center region
Vect3 Region::CalculateCenter()
{
    return (Max+Min)/2.0f;
}

Vect3 Region::CalculateDimensions()
{
    return Max-Min;
}
