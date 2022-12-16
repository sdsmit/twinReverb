//
//  Tremolo.hpp
//  twinReverb - Shared Code
//
//  Created by Sam Smith on 12/15/22.
//

#ifndef Tremolo_hpp
#define Tremolo_hpp

#include <stdio.h>
#include <JuceHeader.h>

class Tremolo
{
public:
    Tremolo();
    ~Tremolo();
    
    //takes in 0-1 speed and 0-1 depth, converts that to be cycles/second, and db depth
    //uses simple sin wave for now
    void processTrem(juce::AudioBuffer<float>& buffer);
    void setDepth(float inDepth);
    void setRate(float inRate);
    
private:
    float depth;
    float rate;
    float t;
};

#endif /* Tremolo_hpp */
