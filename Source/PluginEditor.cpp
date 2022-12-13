/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    gainStage1Value = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, GAIN_STAGE_ONE_ID, gainStage1Slider);
    
    lowShelfGainValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, LOW_SHELF_GAIN_ID, lowShelfGainSlider);
    
    lowShelfFreqValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, LOW_SHELF_FREQ_ID, lowShelfFreqSlider);
    
    addAndMakeVisible(gainStage1Slider);
    gainStage1Slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    gainStage1Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 20);
    gainStage1Slider.setTextValueSuffix("gain");
    gainStage1Slider.setRange(0, 1);
    
    addAndMakeVisible(lowShelfGainSlider);
    lowShelfGainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    lowShelfGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 20);
    lowShelfGainSlider.setTextValueSuffix("lowShelfGain");
    lowShelfGainSlider.setRange(-20, 40);
    
    addAndMakeVisible(lowShelfFreqSlider);
    lowShelfFreqSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    lowShelfFreqSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 20);
    lowShelfFreqSlider.setTextValueSuffix("lowShelfFreq");
    lowShelfFreqSlider.setRange(0, 3000);
    
    setSize (400, 300);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
    gainStage1Value = nullptr;
    lowShelfGainValue = nullptr;
    lowShelfFreqValue = nullptr;
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void NewProjectAudioProcessorEditor::resized()
{
    const int border = 30;
    
    juce::Rectangle<int> gainStageOneArea;
    gainStageOneArea.setBounds(border, border, getWidth()/3, getHeight()/2);
    gainStage1Slider.setBounds(gainStageOneArea);
    
    juce::Rectangle<int> LowShelfGainArea;
    LowShelfGainArea.setBounds(getWidth()/3, border, getWidth()/3, getHeight()/2);
    lowShelfGainSlider.setBounds(LowShelfGainArea);
    
    juce::Rectangle<int> LowShelfFreqArea;
    LowShelfFreqArea.setBounds(getWidth()/3 * 2, border, getWidth()/3, getHeight()/2);
    lowShelfFreqSlider.setBounds(LowShelfFreqArea);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
