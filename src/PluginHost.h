/*
  ==============================================================================

    PluginHost
	by Daniel Rothmann
	This is a tiny audio plugin host which can take care of plugin instantiation
	as well as processing blocks with plugin and setting parameters.

  ==============================================================================
*/

#pragma once

#include "juce_audio_utils/juce_audio_utils.h"

/**
* A tiny audio plugin host which can instantiate plugins, process audio and set parameters.
*/
class PluginHost
{
public:
	PluginHost();
	~PluginHost();

	bool instantiatePlugin(char* xmlPluginDescription, double sampleRate, int bufferSize);
	void prepareToPlay(double sampleRate, int expectedSamplesPerBlock);

    void processBlock(float* buffer, int bufferLength, int numChannels);

    juce::AudioProcessorEditor* pluginEditor;

private:
    std::unique_ptr<juce::AudioPluginFormatManager> formatManager;
    std::unique_ptr<juce::AudioPluginInstance> pluginInstance;
    std::unique_ptr<juce::PluginDescription> pluginDescription;
	bool pluginInstantiated = false;

    std::unique_ptr<juce::AudioBuffer<float>> audioData;
    std::unique_ptr<juce::MidiBuffer> midiData;
};
