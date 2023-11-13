#pragma once

#include <ostream>
#include <math.h>

#define PI 3.14159265f

struct vec2df
{
    vec2df(const float x, const float y) : x(x), y(y)
    {
    };

    vec2df(const vec2df& vec) : x(vec.x), y(vec.y)
    {
    };
    float x;
    float y;

    friend std::ostream& operator<<(std::ostream& os, vec2df const& m)
    {
        return os << m.x << ',' << m.y;
    }
    
    
    bool operator==(const vec2df& other) const
    {
        return (x == other.x && y == other.y);
    }

    vec2df& operator+=(const vec2df& other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }
    
    vec2df& operator-=(const vec2df& other)
    {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }
    
    vec2df& operator*=(const float f)
    {
        this->x *= f;
        this->y *= f;
        return *this;
    }

    vec2df operator*(const float f) const
    {
        return vec2df(this->x * f, this->y * f);
    }

    vec2df operator+(const vec2df& other) const
    {
        vec2df temp(0.0f,0.0f);
        temp.x = this->x + other.x;
        temp.y = this->y + other.y;
        return temp;
    }

    float Magnitude()
    {
        float length = sqrt(x * x + y * y);
        return length;
    }

    vec2df Normalize()
    {
        float mag = Magnitude();
        if (mag == 0)
        {
            return *this;
        }
        this->y = y / mag;
        this->x = x / mag;
        return *this;
    }

    float DiretionToAngleDeg()
    {
        return atan2(this->y, this->x) * 180.0f / PI;
    }

    vec2df AngleDegToDirection(float ang)
    {
        return vec2df(cos(ang / 180.0f * PI), sin(ang / 180.0f * PI));
    }

    vec2df RotateByDeg(float ang)
    {
        float originalAng = this->DiretionToAngleDeg();
        originalAng += ang;
        *this = this->AngleDegToDirection(originalAng);
        return *this;
    }

    float DistanceTo(vec2df target)
    {
        return sqrt((target.x - this->x) * (target.x - this->x) + (target.y - this->y) * (target.y - this->y));
    };
};

class HelpLibrary
{
public:
    HelpLibrary();
    ~HelpLibrary();


    struct vec2dint
    {
        int x;
        int y;
    };
};


// hashing
 template <>
 struct std::hash<vec2df>
 {
     std::size_t operator()(const vec2df& v) const
     {
         std::size_t seed = 17;
         seed = seed * 31 + hash<float>()(v.x);
         seed = seed * 31 + hash<float>()(v.y);
         return seed;
     };
 };
