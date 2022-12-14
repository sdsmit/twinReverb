/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "gainStages.h"
#include "FilterBank.hpp"
#include "Tremolo.hpp"


#define GAIN_STAGE_ONE_ID "gainStageOne"
#define GAIN_STAGE_ONE_NAME "GainStageOne"
#define LOW_SHELF_GAIN_ID "lowShelfGain"
#define LOW_SHELF_GAIN_NAME "LowShelfGain"
#define MID_ID "midKnob"
#define MID_NAME "MidKnob"
#define HIGH_ID "highKnob"
#define HIGH_NAME "HighKnob"
#define SPEED_ID "speedKnob"
#define SPEED_NAME "SpeedKnob"
#define INTENSITY_ID "intensityKnob"
#define INTENSITY_NAME "IntensityKnob"
#define MASTER_ID "masterKnob"
#define MASTER_NAME "MasterKnob"

//==============================================================================
/**
*/
class NewProjectAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    NewProjectAudioProcessor();
    ~NewProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioProcessorValueTreeState treeState;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessor)
    
    GainStages gainStages;
    LowShelf lowShelf;
    HighShelf highShelf;
    Tremolo trem;
};
