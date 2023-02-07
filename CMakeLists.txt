cmake_minimum_required(VERSION 3.13)

include(FetchContent)

project(pluginhost VERSION 0.0.1)

FetchContent_Declare(JUCE
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG        7.0.2
  SOURCE_DIR     ${CMAKE_SOURCE_DIR}/deps/JUCE
)

FetchContent_MakeAvailable(JUCE)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(
  GLOB_RECURSE _source_list
  LIST_DIRECTORIES false
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
  "${_src_root_path}/*.c*"
  "${_src_root_path}/*.h*"
)

juce_add_gui_app(pluginhost
        BUNDLE_ID                       nl.izmar.pluginhost
        MICROPHONE_PERMISSION_ENABLED   TRUE
        PLUGINHOST_VST3                 TRUE)

target_sources(pluginhost PRIVATE ${_source_list})

target_compile_definitions(pluginhost PRIVATE
        JUCE_ALSA=1
        JUCE_DIRECTSOUND=1
        JUCE_DISABLE_CAUTIOUS_PARAMETER_ID_CHECKING=1
        JUCE_PLUGINHOST_LADSPA=1
        JUCE_PLUGINHOST_LV2=1
        JUCE_PLUGINHOST_VST3=1
        JUCE_PLUGINHOST_VST=0
        JUCE_PLUGINHOST_ARA=0
        JUCE_USE_CAMERA=0
        JUCE_USE_CDBURNER=0
        JUCE_USE_CDREADER=0
        JUCE_USE_CURL=0
        JUCE_USE_FLAC=0
        JUCE_USE_OGGVORBIS=1
        JUCE_VST3_HOST_CROSS_PLATFORM_UID=1
        JUCE_WASAPI=1
        JUCE_WEB_BROWSER=0)

target_link_libraries(pluginhost PRIVATE
    juce::juce_audio_utils
    juce::juce_recommended_config_flags
    juce::juce_dsp
    juce::juce_opengl
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags)
