/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainStage1Value;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowShelfGainValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowShelfFreqValue;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;
    juce::Slider gainStage1Slider;
    juce::Label gainStage1Label;
    
    juce::Slider lowShelfGainSlider;
    juce::Label lowShelfGainLabel;
    
    juce::Slider lowShelfFreqSlider;
    juce::Label lowShelfFreqLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
