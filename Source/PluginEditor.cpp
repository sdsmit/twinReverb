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
    
    addAndMakeVisible(gainStage1Slider);
    gainStage1Slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    gainStage1Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 20);
    gainStage1Slider.setTextValueSuffix("gain");
    gainStage1Slider.setRange(0, 1);
    
    setSize (400, 300);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
    gainStage1Value = nullptr;
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    const int border = 30;
    
    juce::Rectangle<int> gainStageOneArea;
    gainStageOneArea.setBounds(border, border, getWidth(), getHeight());
    gainStage1Slider.setBounds(gainStageOneArea);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
