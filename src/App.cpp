#include <memory>

#include "AppWindow.hpp"

#include "PluginHost.h"
#include "PluginsManager.h"

using namespace juce;

class App : public juce::JUCEApplication, private juce::AsyncUpdater
{
private:
    PluginHost host;
    PluginsManager manager;

public:
    App()
    {
    }

    void initialise(const String &commandLine) override
    {
        mainWindow = new AppWindow();
        commandManager.registerAllCommandsForTarget(this);

        char* path = "/Library/Audio/Plug-Ins/VST3/VMPC2000XL.vst3";
        manager.scanAndAdd(path, true);
        auto desc = manager.getXmlPluginDescriptionForFile(path).toStdString();
        bool success = host.instantiatePlugin(&desc[0], 44100, 512);

        assert(success);

        auto editor = host.pluginEditor;

        assert(editor != nullptr);

        mainWindow->setContentOwned(editor, true);
    }

    void handleAsyncUpdate() override
    {
    }

    void shutdown() override
    {
        delete mainWindow;
        mainWindow = nullptr;
        appProperties = nullptr;
        LookAndFeel::setDefaultLookAndFeel(nullptr);
    }

    void suspended() override
    {
#if JUCE_ANDROID || JUCE_IOS
        if (auto graph = mainWindow->graphHolder.get())
            if (auto ioGraph = graph->graph.get())
                ioGraph->saveDocument (PluginGraph::getDefaultGraphDocumentOnMobile());
#endif
    }

    void systemRequestedQuit() override
    {
        JUCEApplicationBase::quit();
    }

    bool backButtonPressed() override
    {
        return true;
    }

    const String getApplicationName() override
    { return "Juce Plug-In Host"; }

    const String getApplicationVersion() override
    { return "0.0.1"; }

    bool moreThanOneInstanceAllowed() override
    { return true; }

    ApplicationCommandManager commandManager;
    std::unique_ptr<ApplicationProperties> appProperties;

private:
    AppWindow *mainWindow;
//    std::unique_ptr<PluginScannerSubprocess> storedScannerSubprocess;
};

START_JUCE_APPLICATION(App)
