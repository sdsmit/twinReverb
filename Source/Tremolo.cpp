//
//  Tremolo.cpp
//  twinReverb - Shared Code
//
//  Created by Sam Smith on 12/15/22.
// process block from ADI tremolo tutorial

#include "Tremolo.hpp"
#include <math.h>

Tremolo::Tremolo()
{
    t = 0.0;
    depth = 1.0;
    rate = .1;
}

Tremolo::~Tremolo()
{
    //nothing to do here
}

void Tremolo::processTrem(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto channelData = buffer.getReadPointer(channel);
        auto channelDataToWrite = buffer.getWritePointer(channel);
        
        for (int samp = 0; samp < buffer.getNumSamples(); samp++)
        {
            auto x_n = channelData[samp];
            
            float trem_factor = 1.0 - (depth*(0.5*sinf(t)+0.5));
             
            // Update t based on rate and a scalar that gets maps our rate roughly between 1Hz and about 20Hz
            t += (rate * 0.002);
             
            // Wrap t if necessary
            if (t > 6.28318531) t -= 6.28318531;
            
            channelDataToWrite[samp] = x_n * trem_factor;
        }
    }
}

void Tremolo::setDepth(float inDepth)
{
    depth = inDepth;
}

void Tremolo::setRate(float inRate)
{
    rate = inRate;
}
