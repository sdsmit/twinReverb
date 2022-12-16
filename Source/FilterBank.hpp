//
//  FilterBank.hpp
//  twinReverb - Shared Code
//
//  Created by Sam Smith on 12/12/22.
//

#ifndef FilterBank_hpp
#define FilterBank_hpp

#include <stdio.h>
#include <JuceHeader.h>

class LowShelf
{
public:
    LowShelf();
    ~LowShelf();
    
    void setSamplingRate(float fsIn);
    void setS(float sIn);
    void computeCoefs(float centerF, float GainDB);
    void applyFilter(juce::AudioBuffer<float>& buffer);
    void mapKnobToFilter(float knobVal);
    
private:
    float mb0;
    float mb1;
    float mb2;
    float ma0;
    float ma1;
    float ma2;
    float mA;
    float mW_0;
    //sampling frequency
    float mFs;
    //center frequency
    float mF0;
    float mAlpha;
    float mS;
    
    float yn_1;
    float yn_2;
    float xn_1;
    float xn_2;
};

class HighShelf
{
public:
    HighShelf();
    ~HighShelf();
    
    void setSamplingRate(float fsIn);
    void setS(float sIn);
    void computeCoefs(float centerF, float GainDB);
    void applyFilter(juce::AudioBuffer<float>& buffer);
    void mapKnobToFilter(float knobVal);
    
private:
    float mb0;
    float mb1;
    float mb2;
    float ma0;
    float ma1;
    float ma2;
    float mA;
    float mW_0;
    //sampling frequency
    float mFs;
    //center frequency
    float mF0;
    float mAlpha;
    float mS;
    
    float yn_1;
    float yn_2;
    float xn_1;
    float xn_2;
};



class FilterBank
{
public:
    FilterBank();
    ~FilterBank();
    
private:
    
    
};

#endif /* FilterBank_hpp */
