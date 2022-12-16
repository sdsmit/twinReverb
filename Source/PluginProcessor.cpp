/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "gainStages.h"

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState(*this, nullptr, "PARAMETERS", {
    std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { GAIN_STAGE_ONE_ID, 1 }, GAIN_STAGE_ONE_NAME, juce::NormalisableRange<float> (0.0f, 1.0f), 0.9f),
    std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { LOW_SHELF_GAIN_ID, 1 }, LOW_SHELF_GAIN_NAME, juce::NormalisableRange<float> (-10.0f, 6.0f), 0.0f),
    std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { MID_ID, 1 }, MID_NAME, juce::NormalisableRange<float> (0.0f, 1.0f), .5f),
    std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { HIGH_ID, 1 }, HIGH_NAME, juce::NormalisableRange<float> (-10.0f, 12.0f), 0.0f),
    std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { SPEED_ID, 1 }, SPEED_NAME, juce::NormalisableRange<float> (0.15f, .9f), 0.5f),
    std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { INTENSITY_ID, 1 }, INTENSITY_NAME, juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f),
    std::make_unique<juce::AudioParameterFloat> (juce::ParameterID { MASTER_ID, 1 }, MASTER_NAME, juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f)
})
#endif
{
    
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
    
}

//==============================================================================
const juce::String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lowShelf.setSamplingRate(sampleRate);
    highShelf.setSamplingRate(sampleRate);
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NewProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    auto gain = treeState.getRawParameterValue(GAIN_STAGE_ONE_ID);
    auto lowShelfGain = treeState.getRawParameterValue(LOW_SHELF_GAIN_ID);
    auto highShelfVal = treeState.getRawParameterValue(HIGH_ID);
    auto midShelfVal = treeState.getRawParameterValue(MID_ID);
    auto speed = treeState.getRawParameterValue(SPEED_ID);
    auto depth = treeState.getRawParameterValue(INTENSITY_ID);
    auto master = treeState.getRawParameterValue(MASTER_ID);
//    gainStages.processFirstStage(buffer, (float)*gain);
    
    //maps knob to filter lookup, computes coefs
//    gainStages.processThirdStage(buffer, 0.4);
    
    lowShelf.mapKnobToFilter((float)*lowShelfGain);
    lowShelf.applyFilter(buffer);
    
    //mid shelf is essentially a volume knob on fender tone stack
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto channelData = buffer.getReadPointer(channel);
        auto channelDataToWrite = buffer.getWritePointer(channel);
        
        for (int samp = 0; samp < buffer.getNumSamples(); samp++)
        {
            channelDataToWrite[samp] = *midShelfVal * channelData[samp];
        }
    }
    
    highShelf.mapKnobToFilter((float)*highShelfVal);
    highShelf.applyFilter(buffer);
    gainStages.processThirdStage(buffer, *gain);
    trem.setRate((float)*speed);
    trem.setDepth((float)*depth);
    trem.processTrem(buffer);
    gainStages.processLowGain(buffer, (float)*master);
}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
