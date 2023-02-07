/*
	==============================================================================

	PluginHost
	by Daniel Rothmann
	This is a tiny audio plugin host which can take care of plugin instantiation
	as well as processing blocks with plugin and setting parameters.

	==============================================================================
*/

#include "PluginHost.h"

#include "juce_audio_processors/juce_audio_processors.h"

/**
*Constructs a host for a single plugin.
*/

using namespace juce;

PluginHost::PluginHost() : pluginEditor(nullptr)
{
	formatManager = std::make_unique<AudioPluginFormatManager>();
	formatManager->addFormat(new VST3PluginFormat());
	audioData = std::make_unique<AudioBuffer<float>>(1, 512);
	midiData = std::make_unique<MidiBuffer>();
}

PluginHost::~PluginHost()
{
}

/**
 *Instantiates a plugin from an XML Document representing a JUCE PluginDescription.
 *@param xmlPluginDescription A string containing the XML Document which can be read as a PluginDescription.
 *@param sampleRate The sample rate to initialize plugin with.
 *@param bufferSize The buffer size to initialize plugin with.
 *@return A boolean representing wether instantiation was successful or not.
*/
bool PluginHost::instantiatePlugin(char* xmlPluginDescription, double sampleRate, int bufferSize)
{
	if (!pluginInstantiated)
	{
		pluginDescription = std::make_unique<PluginDescription>();
		auto document = std::make_unique<XmlDocument>(xmlPluginDescription);
		auto element = document->getDocumentElement();
		
		if (pluginDescription->loadFromXml(*element))
		{
			String error = "Could not create plugin instance.";
			pluginInstance = formatManager->createPluginInstance(*pluginDescription, sampleRate, bufferSize, error);

			if (pluginInstance)
			{
				pluginEditor = pluginInstance->createEditor();
				pluginInstantiated = true;
				return true;
			}
		}
	}

	return false;
}

/**
*Prepares the plugin instance for playback.
*@param sampleRate The sample rate to initialize plugin with.
*@param expectedSamplesPerBlock The maximum buffer size to expect.
*/
void PluginHost::prepareToPlay(double sampleRate, int expectedSamplesPerBlock)
{
	if (pluginInstantiated)
	{
		pluginInstance->setRateAndBufferSizeDetails(sampleRate, expectedSamplesPerBlock);
		pluginInstance->prepareToPlay(sampleRate, expectedSamplesPerBlock);
	}
}

/**
*Processes a block of audio with plugin. If the plugin is not instantiated, the buffer won't be changed.
*@param buffer A buffer of floats containing audio data to be processed.
*@param bufferLength The length of the buffer in samples.
*@param numChannels The total number of channels contained in buffer.
*/
void PluginHost::processBlock(float* buffer, int bufferLength, int numChannels)
{
	if (pluginInstantiated)
	{
		audioData = std::make_unique<AudioBuffer<float>>(&buffer, numChannels, bufferLength);
		audioData->setDataToReferTo(&buffer, numChannels, bufferLength);
		pluginInstance->processBlock(*audioData, *midiData);
	}
}

