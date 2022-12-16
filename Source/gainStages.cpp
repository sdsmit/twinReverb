//
//  gainStages.cpp
//  twinReverb - VST3
//
//  Created by Sam Smith on 12/1/22.
//

#include "gainStages.h"
#include <JuceHeader.h>
#include <math.h>

GainStages::GainStages()
{
    mFirstStageGainScaler = 1.0;
}

GainStages::~GainStages()
{
    
}

//this one is horrible
void GainStages::processFirstStage(juce::AudioBuffer<float>& buffer, float preampGain)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto channelData = buffer.getReadPointer(channel);
        auto channelDataToWrite = buffer.getWritePointer(channel);
        
        for (int samp = 0; samp < buffer.getNumSamples(); samp++)
        {
            float x = channelData[samp] * preampGain;
            if (x > -1 && x < -0.865)
            {
                channelDataToWrite[samp] = (-5.425810591023306*pow(x,3))+(-16.277431773069917*pow(x,2))+(-14.726694523196665*x)+(4.792073341150054);
            }
            if (x > -0.865 && x < -.7)
            {
                channelDataToWrite[samp] = (5.320931985297205*pow(x,3))+(11.610365212481808*pow(x,2))+(9.396249869305576*x)+(2.163375625354759);
            }
            else if (x >= -.7 && x < -.468)
            {
                channelDataToWrite[samp] = (-0.882763766471707*pow(x,3))+(-1.4173958662329071*pow(x,2))+(0.27681711420527616*x)+(0.035507982498022284);
            }
            else if (x >= -.468 && x < 0.502)
            {
                channelDataToWrite[samp] = (0.0752947869734661*pow(x,3))+(-0.07228165719588402*pow(x,2))+(0.906330564034603*x)+(0.13371208067139725);
            }
            else if (x >= 0.502 && x < 0.726)
            {
                channelDataToWrite[samp] = (0.5850801542272028*pow(x,3))+(0.9222430042523234*pow(x,2))+(0.40707918398760284*x)+(0.2172534782659286);
            }
            else if (x >= 0.726 && x < 0.946)
            {
                channelDataToWrite[samp] = (-2.684731294488553*pow(x,3))+(5.495283187741544*pow(x,2))+(-2.912947989225571*x)+(1.0207000541835167);
            }
            else if (x >= 0.946 && x < 0.994)
            {
                channelDataToWrite[samp] = (14.749890458451176*pow(x,3))+(-43.984173347101404*pow(x,2))+(43.89461789273586*x)+(-13.739285720594987);
            }
            else
            {
                channelDataToWrite[samp] = .92;
            }
        }
    }
}


//this one sounds good
void GainStages::processThirdStage(juce::AudioBuffer<float>& buffer, float preampGain)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto channelData = buffer.getReadPointer(channel);
        auto channelDataToWrite = buffer.getWritePointer(channel);
        
        for (int samp = 0; samp < buffer.getNumSamples(); samp++)
        {
            float x = channelData[samp] * preampGain * 1.2;
            if (x < -.53)
            {
                channelDataToWrite[samp] = -0.89;
            }
            else if (x > -0.5336048 && x < -0.4166702)
            {
                channelDataToWrite[samp] = 12.543690477021165*pow(x,3)+20.08012034475835*pow(x,2)+11.88227665905797*x+1.6386713638534254;
                
            }
            else if (x > -0.4166702 && x < 0.03968989)
            {
                channelDataToWrite[samp] = -5.700289897938278*pow(x,3)-2.725048510132929*pow(x,2)+2.380042391256649*x+0.3189054129162155;
            
            }
            else if (x > 0.03968989 && x < 0.1982797)
            {
                channelDataToWrite[samp] = -3.9638605931691795*pow(x,3)-2.931804574430115*pow(x,2)+2.388248516705437*x+0.31879684617741927;
                
            }
            else if (x > 0.1982797 && x < 0.2749234)
            {
                channelDataToWrite[samp] = 21.584086808245132*pow(x,3)-18.128722613534745*pow(x,2)+5.4014888664236915*x+0.11964204865407578;
                
            }
            else if (x > 0.2749234 && x < 0.8313219)
            {
                channelDataToWrite[samp] = 0.11784032719937629*pow(x,3)-0.42400221011333855*pow(x,2)+0.5340469370657069*x+0.565699943494628;
                
            }
            else if (x > 0.8313219 && x < 0.9411683)
            {
                channelDataToWrite[samp] = 0.39483155873813197*pow(x,3)-1.1148088407717534*pow(x,2)+1.1083296177972586*x+0.4065620204003457;
            }
            else
            {
                channelDataToWrite[samp] = 0.79;
            }
            channelDataToWrite[samp] -= .15;
        }
    }
}


//this one sounds good
void GainStages::processLowGain(juce::AudioBuffer<float>& buffer, float preampGain)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto channelData = buffer.getReadPointer(channel);
        auto channelDataToWrite = buffer.getWritePointer(channel);
        
        for (int samp = 0; samp < buffer.getNumSamples(); samp++)
        {
            float x = channelData[samp] * preampGain;
            if (x < -.9982361)
            {
                channelDataToWrite[samp] = -0.92;
            }
            else if (x > -0.9982361 && x < -0.8099695)
            {
                channelDataToWrite[samp] = 0.031232236081167566*pow(x,3)+0.09353143661983199*pow(x,2)+1.0453339744209469*x+0.060853098206049165;
            }
            else if (x > -0.8099695 && x < -0.3499204)
            {
                channelDataToWrite[samp] = -0.009808670976857477*pow(x,3)-0.006194212288173061*pow(x,2)+0.9645592404377544*x+0.039044741240382715;
            }
            else if (x > -0.3499204 && x < -0.003321694)
            {
                channelDataToWrite[samp] = -0.0563974369207664*pow(x,3)-0.05510129113197003*pow(x,2)+0.9474456558459015*x+0.03704861045177771;
            }
            else if (x > -0.003321694 && x < 0.5440722)
            {
                channelDataToWrite[samp] = -0.06287450130785989*pow(x,3)-0.05516583560970669*pow(x,2)+0.947445441448897*x+0.037048610214390626;
                
            }
            else if (x > 0.5440722 && x < 0.9372727)
            {
                channelDataToWrite[samp] = -0.3117542250860701*pow(x,3)+0.3510597809445028*pow(x,2)+0.7264293765538918*x+0.07713150910198004;
                
            }
            else if (x > 0.9372727 && x < 0.9993369)
            {
                channelDataToWrite[samp] = 2.822541776117758*pow(x,3)-8.462010445998043*pow(x,2)+8.986679503449944*x-2.5035708039350886*x;
            }
            else
            {
                channelDataToWrite[samp] = 0.84;
            }
        }
    }
}

