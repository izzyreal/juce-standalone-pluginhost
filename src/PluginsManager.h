/*
	==============================================================================

	Plugins Manager
	by Daniel Rothmann

	A wrapper class for the JUCE KnownPluginList for C# interop

	==============================================================================
*/

#pragma once

#include "juce_audio_utils/juce_audio_utils.h"

class PluginsManager
{
public:
	PluginsManager();

	bool scanAndAdd(char* filePath, bool dontRescanIfAlreadyInList);
    juce::String getXmlPluginDescriptionForFile(char* filePath);

private:
	std::unique_ptr<juce::KnownPluginList> pluginList;
    std::unique_ptr<juce::AudioPluginFormat> pluginFormat;
	juce::OwnedArray<juce::PluginDescription> descriptions;

    juce::String convertXmlElementToString(juce::XmlElement* element);

};
