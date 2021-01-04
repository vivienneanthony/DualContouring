// Vivienne Anthony
// 2021
#include <iostream>

#include "MeshData.h"

#include "../Util/Vect3.h"
#include "../Noise/FastNoiseLite.h"

MeshData::MeshData()
{
    //ctor
}

MeshData::~MeshData()
{
    if(randomPoints)
    {
        randomPoints->clear();

        delete randomPoints;
    }
}

// Creat Mesh Data
void MeshData::CreateMeshData(Shape inshape)
{

    // Create and configure FastNoise object
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);


    // create data
    randomPoints = new std::vector<PointV3>();

    // create blank value
    float value = 0.0f;
    float distance = 0.0f;
    PointV3 newData;

    std::cout << "Building Data" << std::endl;

    if(inshape == Shape::Terrain)
    {
        // test solid object with caverns
        for (unsigned int z = 0; z< 1024; z+=4)
        {
            for (unsigned  y = 0; y < 1024; y+=4)
            {
                for (unsigned int x = 0; x < 1024; x+=4)
                {
                    value = noise.GetNoise((float)x, (float)y, (float)z);

                    distance = Vect3(x,y,z).CalculateDistance(Vect3(1024.0f/2.0f,1024.0f/2.0f,1024.0f/2.0f));

                    // use noise
                    value>.50f?value=1.0f:value=0;

                    if(distance>512)
                    {
                        value=0;
                    }

                    // set basic value
                    newData.v = Vect3((float)x,(float)y,(float)z);
                    newData.n = Vect3(1.0f,1.0f,1.0f)*value;

                    // add data
                    randomPoints->push_back(newData);

                }
            }
        }
    }

    std::cout << "Built Point Data " <<std::endl;
}

std::vector<PointV3> MeshData::GetData()
{
    std::vector<PointV3> outData;

    if(randomPoints)
    {
        while(randomPoints->size())
        {
            outData.push_back(randomPoints->back());
            randomPoints->pop_back();
        }
    }

    return outData;
}
