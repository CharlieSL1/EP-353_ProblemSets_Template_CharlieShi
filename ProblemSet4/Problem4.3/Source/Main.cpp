/*
  ==============================================================================
    
    What I do in this code:
      Generates a 250 Hz sine wave and applies a 2 Hz tremolo via a unipolar LFO.
      The LFO is phase-shifted so the output starts at amplitude = 0.

    How it works:
      - Sample rate: 44100 Hz
      - Duration:    2 seconds
      - Tremolo LFO: 2 Hz, unipolar [0..1], starts from 0 amplitude at t=0
      - Output:      "tremolo.wav"

  ==============================================================================
*/

#include <JuceHeader.h>
#include <cmath>

//==============================================================================
// Helper function: Returns a sine wave sample given the phase [0..1).
//==============================================================================
inline float sineSample (double phase)
{
    // phase in [0,1) => angle in [0, 2π)
    double angle = phase * juce::MathConstants<double>::twoPi;
    return static_cast<float> (std::sin (angle));
}

//==============================================================================
// main()
//==============================================================================
int main (int argc, char* argv[])
{
    // 1) Set parameters
    const double sampleRate      = 44100.0;
    const double durationSeconds = 2.0;
    const int    numSamples      = static_cast<int> (durationSeconds * sampleRate);

    const float mainFreq = 250.0f; // primary sine wave frequency
    const float lfoFreq  = 2.0f;   // LFO for tremolo
    const float mainAmp  = 1.0f;   // overall amplitude scaling (up to 1.0)

    // 2) Create an AudioSampleBuffer for stereo output
    juce::AudioSampleBuffer buffer (2, numSamples);
    buffer.clear();

    // 3) Prepare phase increments for main wave & LFO
    double mainPhaseInc = mainFreq / sampleRate;  // how much main wave phase advances per sample
    double lfoPhaseInc  = lfoFreq  / sampleRate;  // how much LFO phase advances per sample

    // 4) We want the LFO to start at amplitude = 0. Normally:
    //    sin(0) = 0 => mapped to [0..1] => 0.5
    //    To start at 0.0 amplitude, we need sin(...)= -1 at t=0.
    //    That occurs at angle -π/2, 3π/2, etc. We can shift phase by -π/2 in the domain [0..1).
    //    So lfoPhase = -0.25f (which is -π/2 in the normalized [0..1) domain).
    double mainPhase = 0.0;
    double lfoPhase  = -0.25; // - π/2 in normalized 0..1

    // 5) Generate samples
    for (int i = 0; i < numSamples; ++i)
    {
        // Main wave:  -1..+1
        float mainValue = sineSample (std::fmod (mainPhase, 1.0));

        // LFO wave:   -1..+1
        float lfoValue = sineSample (std::fmod (lfoPhase, 1.0));

        // Convert LFO from bipolar [-1..1] -> unipolar [0..1]
        // unipolar = (lfoValue + 1.0f) * 0.5f
        float unipolarLfo = 0.5f * (lfoValue + 1.0f);

        // Multiply main wave by unipolar LFO
        float outSample = mainAmp * mainValue * unipolarLfo;

        // Write to stereo channels
        for (int channel = 0; channel < 2; ++channel)
            buffer.setSample (channel, i, outSample);

        // Advance phases
        mainPhase += mainPhaseInc;
        lfoPhase  += lfoPhaseInc;
    }

    // 6) Write to "tremolo.wav"
    juce::File outFile ("tremolo.wav");
    if (outFile.existsAsFile())
        outFile.deleteFile();

    juce::WavAudioFormat wavFormat;
    if (auto outStream = outFile.createOutputStream())
    {
        if (auto writer = wavFormat.createWriterFor (outStream.get(),
                                                     sampleRate,
                                                     (unsigned int) buffer.getNumChannels(),
                                                     16,
                                                     {},
                                                     0))
        {
            outStream.release(); // pass stream to writer
            writer->writeFromAudioSampleBuffer (buffer, 0, buffer.getNumSamples());
        }
    }

    return 0;
}
