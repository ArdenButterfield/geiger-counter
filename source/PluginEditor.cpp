// Nathan Blair January 2023

#include "PluginEditor.h"
#include "interface/ParameterSlider.h"
#include "parameters/StateManager.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    state = processorRef.state.get();
    startTimerHz(int(TIMER_HZ));

    // INIT UNDO/REDO
    undo_manager = state->get_undo_manager();

    radiation_slider = std::make_unique<ParameterSlider>(state, PARAM::RADIATION);
    frequency_slider = std::make_unique<ParameterSlider>(state, PARAM::FREQUENCY);
    speaker_slider = std::make_unique<ParameterSlider>(state, PARAM::SPEAKER);
    room_slider = std::make_unique<ParameterSlider>(state, PARAM::ROOM);
    gain_slider = std::make_unique<ParameterSlider>(state, PARAM::GAIN);

    addAndMakeVisible(*radiation_slider);
    addAndMakeVisible(*frequency_slider);
    addAndMakeVisible(*speaker_slider);
    addAndMakeVisible(*room_slider);
    addAndMakeVisible(*gain_slider);

    // some settings about UI
    setOpaque (true);
    setSize(W, H);
    setColour(0, juce::Colour(0xff00ffa1)); // background color
    
    // resizable window
    setResizable(true, true);
    setResizeLimits((W * 4) / 5, (H * 4) / 5, (W * 3) / 2, (H * 3) / 2);
    getConstrainer()->setFixedAspectRatio(float(W) / float(H));
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    // remove any listeners here

    // also, if we have a lookAndFeel object we should call:
    // setLookAndFeel(nullptr); 
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Our component is opaque, so we must completely fill the background with a solid colour
    g.fillAll(findColour(0));
}

void AudioPluginAudioProcessorEditor::resized()
{
    // set the position of your components here
    int slider_size = proportionOfWidth(0.1f);
    int slider_x = proportionOfWidth(0.5f) - (slider_size * 5/2 );
    int slider_y = proportionOfHeight(0.5f) - (slider_size / 2);
    radiation_slider->setBounds(slider_x, slider_y, slider_size, slider_size);
    frequency_slider->setBounds(slider_x + slider_size, slider_y, slider_size, slider_size);
    speaker_slider->setBounds(slider_x + slider_size * 2, slider_y, slider_size, slider_size);
    room_slider->setBounds(slider_x + slider_size * 3, slider_y, slider_size, slider_size);
    gain_slider->setBounds(slider_x + slider_size * 4, slider_y, slider_size, slider_size);
}

void AudioPluginAudioProcessorEditor::timerCallback() {
    // repaint UI and note that we have updated ui, if parameter values have changed
    if (state->any_parameter_changed.exchange(false)) {
        if (state->get_parameter_modified(PARAM::RADIATION)) {
            radiation_slider->repaint();
        }
        if (state->get_parameter_modified(PARAM::FREQUENCY)) {
            frequency_slider->repaint();
        }
        if (state->get_parameter_modified(PARAM::SPEAKER)) {
            speaker_slider->repaint();
        }
        if (state->get_parameter_modified(PARAM::ROOM)) {
            room_slider->repaint();
        }
        if (state->get_parameter_modified(PARAM::GAIN)) {
            gain_slider->repaint();
        }
    }

    state->update_preset_modified();

    if (timer_counter % (TIMER_HZ / UNDO_HZ) == 0 ) {
        if (!isMouseButtonDownAnywhere()) {
            processorRef.state->get_undo_manager()->beginNewTransaction();
        }
    }

    timer_counter++;
}