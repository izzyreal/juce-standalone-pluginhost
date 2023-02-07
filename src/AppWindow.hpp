#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include "juce_audio_processors/juce_audio_processors.h"

class AppWindow : public juce::DocumentWindow
{
public:
    AppWindow() : juce::DocumentWindow(
            "PluginHost",
            juce::Colours::aliceblue,
            DocumentWindow::minimiseButton | DocumentWindow::closeButton
    )
    {
        setResizable(true, false);
        setResizeLimits(500, 400, 10000, 10000);
        centreWithSize(800, 600);
        setUsingNativeTitleBar(true);
        setVisible(true);
    }
};