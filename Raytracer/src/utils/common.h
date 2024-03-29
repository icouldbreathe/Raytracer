#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi       = 3.1415926535897932385;

// Utility Functions

inline double degreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double randomDouble()
{
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max)
{
    return min + (max - min) * randomDouble();
}

inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

// Common Headers

#include "Ray.h"
#include "Vec3.h"