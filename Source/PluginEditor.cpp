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
    midValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, MID_ID, midSlider);
    highValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, HIGH_ID, highSlider);
    speedValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, SPEED_ID, speedSlider);
    intensityValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, INTENSITY_ID, intensitySlider);
    masterValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, MASTER_ID, masterSlider);
    
    addAndMakeVisible(gainStage1Slider);
    gainStage1Slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    gainStage1Slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 20);
    gainStage1Slider.setTextValueSuffix("gain");
    gainStage1Slider.setRange(0, 1);
    
    addAndMakeVisible(gainStage1Label);
    gainStage1Label.attachToComponent(&gainStage1Slider, false);
    gainStage1Label.setText("Volume", juce::NotificationType::dontSendNotification);
    gainStage1Label.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(lowShelfGainSlider);
    lowShelfGainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    lowShelfGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 20);
    lowShelfGainSlider.setTextValueSuffix("Low");
    lowShelfGainSlider.setRange(-10.0f, 6.0f);
    
    addAndMakeVisible(lowShelfGainLabel);
    lowShelfGainLabel.attachToComponent(&lowShelfGainSlider, false);
    lowShelfGainLabel.setText("Low", juce::NotificationType::dontSendNotification);
    lowShelfGainLabel.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(midSlider);
    midSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    midSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 20);
    midSlider.setTextValueSuffix("Mid");
    midSlider.setRange(0, 3000.0f);
    
    addAndMakeVisible(midLabel);
    midLabel.attachToComponent(&midSlider, false);
    midLabel.setText("Mid", juce::NotificationType::dontSendNotification);
    midLabel.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(highSlider);
    highSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    highSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 20);
    highSlider.setTextValueSuffix("High");
    highSlider.setRange(-10.0f, 12.0f);
    
    addAndMakeVisible(highLabel);
    highLabel.attachToComponent(&highSlider, false);
    highLabel.setText("High", juce::NotificationType::dontSendNotification);
    highLabel.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(speedSlider);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    speedSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 20);
    speedSlider.setTextValueSuffix("speed");
    speedSlider.setRange(0.15, .9);
    
    addAndMakeVisible(speedLabel);
    speedLabel.attachToComponent(&speedSlider, false);
    speedLabel.setText("Speed", juce::NotificationType::dontSendNotification);
    speedLabel.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(intensitySlider);
    intensitySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    intensitySlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 20);
    intensitySlider.setTextValueSuffix("intensity");
    intensitySlider.setRange(0., .7);
    
    addAndMakeVisible(intensityLabel);
    intensityLabel.attachToComponent(&intensitySlider, false);
    intensityLabel.setText("intensity", juce::NotificationType::dontSendNotification);
    intensityLabel.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(masterSlider);
    masterSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    masterSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 70, 20);
    masterSlider.setTextValueSuffix("master");
    masterSlider.setRange(0, 3000);
    
    addAndMakeVisible(masterLabel);
    masterLabel.attachToComponent(&masterSlider, false);
    masterLabel.setText("master", juce::NotificationType::dontSendNotification);
    masterLabel.setJustificationType(juce::Justification::centred);
    
    setSize (1000, 300);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
    gainStage1Value = nullptr;
    lowShelfGainValue = nullptr;
    midValue = nullptr;
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
    float knobWidth = (getWidth() - (2*border)) / 7;
    
    juce::Rectangle<int> gainStageOneArea;
    gainStageOneArea.setBounds(0, border, knobWidth, getHeight());
    gainStage1Slider.setBounds(gainStageOneArea);
    
    juce::Rectangle<int> LowShelfGainArea;
    LowShelfGainArea.setBounds((getWidth()/7), border, knobWidth, getHeight());
    lowShelfGainSlider.setBounds(LowShelfGainArea);
    
    juce::Rectangle<int> midArea;
    midArea.setBounds((getWidth()/7 * 2), border, knobWidth, getHeight());
    midSlider.setBounds(midArea);
    
    juce::Rectangle<int> highArea;
    highArea.setBounds((getWidth()/7 * 3), border, knobWidth, getHeight());
    highSlider.setBounds(highArea);
    
    juce::Rectangle<int> speedArea;
    speedArea.setBounds((getWidth()/7 * 4), border, knobWidth, getHeight());
    speedSlider.setBounds(speedArea);
    
    juce::Rectangle<int> intensityArea;
    intensityArea.setBounds((getWidth()/7 * 5), border, knobWidth, getHeight());
    intensitySlider.setBounds(intensityArea);
    
    juce::Rectangle<int> masterArea;
    masterArea.setBounds((getWidth()/7 * 6), border, knobWidth, getHeight());
    masterSlider.setBounds(masterArea);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
