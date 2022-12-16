//
//  Tremolo.cpp
//  twinReverb - Shared Code
//
//  Created by Sam Smith on 12/15/22.
//

#include "Tremolo.hpp"
#include <math.h>


void Tremolo::setW(float inFS)
{
    w = 2 * M_PI / inFS;
}

void Tremolo::setTrem(float inSpeed, float inDepth)
{
    depth = inDepth;
}
