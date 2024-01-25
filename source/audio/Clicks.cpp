//
// Created by arden on 1/21/24.
//

#include "Clicks.h"

Clicks::Clicks()
{
    samplerate = 44100;
}

Clicks::~Clicks()
{

}

void Clicks::reset()
{
    random.setSeedRandomly();
    curr_level = 1;
    dt_counter = 0;
    rt_counter = 0;
}

void Clicks::setClicksPerSecond (float nClicks)
{
    probability = nClicks / samplerate;
}

void Clicks::setProbability (float prob)
{
    probability = prob;
}

bool Clicks::radiationEvent()
{
    return (random.nextFloat() < probability);
}

float Clicks::tick()
{
    /*
     * See Costrell, L. (1949). Accurate determination of the deadtime and recovery characteristics of Geiger-Muller counters. J. Res. Natl. Bur. Stand, 42(3), 241-249.
     */
    // Once the dead time is up, we enter the recovery time.
    if (dt_counter == 1) {
        rt_counter = recovery_time;
    }
    // Tick both counters forward.
    if (dt_counter > 0) {
        dt_counter -= 1;
    }

    if (rt_counter > 0) {
        rt_counter -= 1;
    }

    if (radiationEvent() && (dt_counter == 0)) {
        // We got a hit, and we are not in the dead time of the
        // last hit.
        // The strength of this tick depends on how much we have recovered from the
        // previous tick.
        float amount_recovered = (float) (recovery_time - rt_counter) / (float) (recovery_time);
        int dt = (int) ((float) max_deadtime * amount_recovered);
        dt_counter = dt;
        if (dt == 0) {
            rt_counter = recovery_time;
        }
        return amount_recovered;
    } else {
        return 0.0;
    }
}

void Clicks::process (float* data, int numSamples)
{
    for (int s = 0; s < numSamples; ++s) {
        data[s] += tick();
    }
}
void Clicks::setSamplerate (float _samplerate)
{
    samplerate = _samplerate;
}
