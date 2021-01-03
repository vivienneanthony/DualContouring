#ifndef REGION_H
#define REGION_H

// Vivienne Anthony
// 2021

#include "Vect3.h"

class Region
{
public:
    Region();                                                           // Constructor
    ~Region();                                                          // Deconstructor

    Region(Vect3 inMin, Vect3 inMax);                                   // Construction region

    // Set Region
    void SetRegion(Vect3 inMin, Vect3 inMax);                           // Set Region

    Vect3 CalculateCenter();                                            // Calculate Center

    Vect3 CalculateDimensions();                                        // Get dimension

    Vect3 Min;                                                          // Store mid
    Vect3 Max;                                                          // Store max

};

#endif
