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
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> midValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> speedValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> intensityValue;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterValue;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;
    juce::Slider gainStage1Slider;
    juce::Label gainStage1Label;
    
    juce::Slider lowShelfGainSlider;
    juce::Label lowShelfGainLabel;
    
    juce::Slider midSlider;
    juce::Label midLabel;
    
    juce::Slider highSlider;
    juce::Label highLabel;
    
    juce::Slider speedSlider;
    juce::Label speedLabel;
    
    juce::Slider intensitySlider;
    juce::Label intensityLabel;
    
    juce::Slider masterSlider;
    juce::Label masterLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
