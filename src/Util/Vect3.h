#ifndef VECT3_H
#define VECT3_H

// Vivienne Anthony
// 2020

class Vect3
{
public:
    // constructor and deconstructor
    Vect3()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    };

    Vect3(float inX, float inY, float inZ)
    {
        x = inX;
        y = inY;
        z = inZ;
    };

    ~Vect3() {};

    // variables
    float x;
    float y;
    float z;


    /// Add-assign a vector.
    Vect3& operator +=(const Vect3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    /// Subtract-assign a vector.
    Vect3& operator -=(const Vect3& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    /// Multiply-assign a scalar.
    Vect3& operator *=(int rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    /// Multiply-assign a vector.
    Vect3& operator *=(const Vect3& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }

    /// Divide-assign a scalar.
    Vect3& operator /=(int rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    /// Divide-assign a scalar.
    Vect3& operator /(float rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    /// Divide-assign a vector.
    Vect3& operator /=(const Vect3& rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    /// Divide-assign a vector.
    Vect3& operator -(const Vect3& rhs)
    {
        x -= rhs.x;
        y -=rhs.y;
        z -= rhs.z;

        return *this;
    }

    /// Divide-assign a vector.
    Vect3& operator +(const Vect3& rhs)
    {
        Vect3 outVect3;

        x +=  rhs.x;
        y +=  rhs.y;
        z += rhs.z;


        return *this;
    }

};


class PointV3
{
public:
    // constructor and deconstructor
    PointV3()
    {
        Vect3 vertex;
        Vect3 normal;
    };

    ~PointV3() {};


};



#endif
