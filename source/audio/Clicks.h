//
// Created by arden on 1/21/24.
//

#ifndef GEIGER_CLICKS_H
#define GEIGER_CLICKS_H

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_core/juce_core.h>

class Clicks
{
public:
    Clicks();
    ~Clicks();
    void setSamplerate(float _samplerate);
    void setClicksPerSecond(float nClicks);
    void setProbability(float prob);
    bool radiationEvent();
    float tick();
    void reset();
    void process(float* data, int numSamples);
private:
    float samplerate;
    float probability;
    juce::Random random;

    int max_deadtime = 4000;
    int recovery_time = 4000;

    float curr_level;

    int dt_counter;
    int rt_counter;
};

#endif //GEIGER_CLICKS_H
