#include "math.h"

int Math::calculateSegments(float radius)
{
    int segments = static_cast<int>(radius * 2); 

    const int minSegments = 16;

    const int maxSegments = 128; // max 128 dla performance

    if (segments < minSegments) segments = minSegments; 
    if (segments > maxSegments) segments = maxSegments;

    return segments;
}
