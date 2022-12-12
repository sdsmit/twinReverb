//
//  gainStages.hpp
//  twinReverb - VST3
//
//  Created by Sam Smith on 12/1/22.
//

#ifndef gainStages_h
#define gainStages_h

#include <stdio.h>
#include <JuceHeader.h>

class GainStages
{
public:
    GainStages();
    ~GainStages();
    
    
    void processFirstStage(juce::AudioBuffer<float>& buffer, float preampGain);
    void processThirdStage(juce::AudioBuffer<float>& buffer, float preampGain);
    
private:
    
    float mFirstStageGainScaler = 0.0;
    float mThirdStageGainScaler = 0.0;
    
};

#endif /* gainStages_hpp */
