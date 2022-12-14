//
//  FilterBank.cpp
//  twinReverb - Shared Code
//
//  Created by Sam Smith on 12/12/22.
//

#include "FilterBank.hpp"
#include <math.h>

namespace {
float clip(float n, float lower, float upper) {
    return std::max(lower, std::min(n, upper));
}

float scaleBetween(float unscaledNum, float minAllowed, float maxAllowed, float min, float max) {
    return (maxAllowed - minAllowed) * (unscaledNum - min) / (max - min) + minAllowed;
}
};

LowShelf::LowShelf()
{
    yn_1 = 0;
    yn_2 = 0;
    xn_1 = 0;
    xn_2 = 0;
}

LowShelf::~LowShelf()
{
    
}

void LowShelf::setSamplingRate(float fsIn)
{
    mFs = fsIn;
}

void LowShelf::setS(float sIn)
{
    mS = sIn;
}

void LowShelf::computeCoefs(float centerF, float GainDB)
{
    mW_0 = 2 * M_PI * (centerF / mFs);
    mA = pow(10,GainDB/40);
    mAlpha = (sin(mW_0) / 2) * sqrt((mA + (1/mA)) * ((1/mS) - 1) + 2);
    
    mb0 = mA *((mA + 1) - (mA - 1) * cos(mW_0) + 2 * sqrt(mA) * mAlpha);
    mb1 = 2 * mA * ((mA - 1) - (mA + 1) * cos(mW_0));
    mb2 = mA * ((mA + 1) - (mA - 1) * cos(mW_0) - 2 * sqrt(mA) * mAlpha);
    ma0 = (mA + 1) + (mA - 1) * cos(mW_0) + 2 * sqrt(mA) * mAlpha;
    ma1 = -2 * ((mA - 1) + (mA + 1) * cos(mW_0));
    ma2 = (mA + 1) + (mA - 1) * cos(mW_0) - 2 * sqrt(mA) * mAlpha;
}

void LowShelf::applyFilter(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto channelData = buffer.getReadPointer(channel);
        auto channelDataToWrite = buffer.getWritePointer(channel);
        
        for (int samp = 0; samp < buffer.getNumSamples(); samp++)
        {
            auto x_n = channelData[samp];
            
            auto y_0 = ((mb0 / ma0) * x_n) + ((mb1 / ma0) * xn_1) + ((mb2 / ma0) * xn_2) -
            ((ma1 / ma0) * yn_1) - ((ma2 / ma0) * yn_2);
            
            xn_2 = xn_1;
            xn_1 = x_n;
            yn_2 = yn_1;
            yn_1 = y_0;
            
            channelDataToWrite[samp] = y_0;
        }
    }
}

void LowShelf::mapKnobToFilter(float knobVal)
{
    //map 0-1 to gain/freq pair, probably use some logrithmic scaling thing here
    float knobClipped = clip(knobVal, 0.01f, 1.0f);
    float freqMapped = scaleBetween(knobClipped, 700.0f, 400.0f, 0.0f, 1.0f);
    setS(1.0);
    computeCoefs(freqMapped, knobVal);
}

HighShelf::HighShelf()
{
    yn_1 = 0;
    yn_2 = 0;
    xn_1 = 0;
    xn_2 = 0;
}

HighShelf::~HighShelf()
{
    
}

void HighShelf::setSamplingRate(float fsIn)
{
    mFs = fsIn;
}

void HighShelf::setS(float sIn)
{
    mS = sIn;
}

void HighShelf::computeCoefs(float centerF, float GainDB)
{
    mW_0 = 2 * M_PI * (centerF / mFs);
    mA = GainDB;
    mAlpha = (sin(mW_0) / 2) * sqrt((mA + (1/mA)) * ((1/mS) - 1) + 2);
    
    mb0 = mA *((mA + 1) + (mA - 1) * cos(mW_0) + 2 * sqrt(mA) * mAlpha);
    mb1 = -2 * mA * ((mA - 1) + (mA + 1) * cos(mW_0));
    mb2 = mA * ((mA + 1) + (mA - 1) * cos(mW_0) - 2 * sqrt(mA) * mAlpha);
    ma0 = (mA + 1) - (mA - 1) * cos(mW_0) + 2 * sqrt(mA) * mAlpha;
    ma1 = 2 * ((mA - 1) - (mA + 1) * cos(mW_0));
    ma2 = (mA + 1) - (mA - 1) * cos(mW_0) - 2 * sqrt(mA) * mAlpha;
}

void HighShelf::applyFilter(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto channelData = buffer.getReadPointer(channel);
        auto channelDataToWrite = buffer.getWritePointer(channel);
        
        for (int samp = 0; samp < buffer.getNumSamples(); samp++)
        {
            auto x_n = channelData[samp];
            
            auto y_0 = ((mb0 / ma0) * x_n) + ((mb1 / ma0) * xn_1) + ((mb2 / ma0) * xn_2) -
            ((ma1 / ma0) * yn_1) - ((ma2 / ma0) * yn_2);
            
            xn_2 = xn_1;
            xn_1 = x_n;
            yn_2 = yn_1;
            yn_1 = y_0;
            
            channelDataToWrite[samp] = y_0;
        }
    }
}

