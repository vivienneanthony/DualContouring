#ifndef REGION_H
#define REGION_H

// Vivienne Anthony
// 2021

#include "Vect3.h"

class Region
{
public:
    Region();
    ~Region();

    // Set Initial
    Region(Vect3 inMin, Vect3 inMax);

    // Set Region
    void SetRegion(Vect3 inMin, Vect3 inMax);

    Vect3 CalculateCenter();

    Vect3 CalculateDimensions();

    Vect3 Min;
    Vect3 Max;

};

#endif
