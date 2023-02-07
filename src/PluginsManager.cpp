#include "PluginsManager.h"

using namespace juce;

PluginsManager::PluginsManager()
{
	pluginList = std::make_unique<KnownPluginList>();
	pluginFormat = std::make_unique<VST3PluginFormat>();
	descriptions = OwnedArray<PluginDescription>();
}

bool PluginsManager::scanAndAdd(char* filePath, bool dontRescanIfAlreadyInList)
{
	return pluginList->scanAndAddFile(filePath, dontRescanIfAlreadyInList, descriptions, *pluginFormat);
}

String PluginsManager::getXmlPluginDescriptionForFile(char* filePath)
{
	auto description = pluginList->getTypeForFile(filePath);

	if (description)
	{
		return convertXmlElementToString(description->createXml().get());
	}

	return "";
}

String PluginsManager::convertXmlElementToString(XmlElement* element)
{
	return element->toString();
}
