/*
  ==============================================================================
    The template DAFx file (modified to generate a triangle wave).
  ==============================================================================
*/

// This gets generated dynamically by CMake. VSCode will complain it can't
// find it until you generate the CMake build directory
#include <JuceHeader.h>
#include <cmath>
#include <iostream>

// Function prototypes
int readSoundFile (juce::AudioBuffer<float>* buffer);
int writeSoundFile (juce::AudioBuffer<float> buffer, float sampleRate);
void process (juce::AudioBuffer<float> inBuffer, juce::AudioBuffer<float>* outBuffer, float sampleRate);

//==============================================================================
int main ()
{
    // 1) Read the source file into a buffer
    juce::AudioBuffer<float> inBuffer;
    float sampleRate = readSoundFile (&inBuffer);

    // If reading fails (returns 0), you could set a default sampleRate (e.g., 44100.0f).
    // For demonstration, we will just exit if sampleRate <= 0.
    if (sampleRate <= 0.0f)
        return 1;

    // 2) Create an output buffer. For now, set it to the same size as inBuffer.
    juce::AudioBuffer<float> outBuffer (inBuffer.getNumChannels(), inBuffer.getNumSamples());

    // 3) Process (in this case, generate a triangle wave into outBuffer).
    process (inBuffer, &outBuffer, sampleRate);

    // 4) Write the result to a new WAV file
    if (writeSoundFile (outBuffer, sampleRate))
        return 1;

    return 0;
}

//==============================================================================
// A helper function to generate a single sample of a triangle wave.
// Phase should be in [0.0, 1.0), and the function returns a value in [-1.0, +1.0].
//==============================================================================
float generateTriangleSample (float phase)
{
    // 0 <= phase < 0.5: ramp from -1 to +1
    // 0.5 <= phase < 1.0: ramp from +1 to -1
    if (phase < 0.5f)
    {
        return -1.0f + phase * 4.0f;   // slope up
    }
    else
    {
        return 3.0f - phase * 4.0f;    // slope down
    }
}

//==============================================================================
// This function has been modified to generate a triangle wave instead of
// copying from inBuffer to outBuffer.
//==============================================================================
void process (juce::AudioBuffer<float> inBuffer,
              juce::AudioBuffer<float>* outBuffer,
              float sampleRate)
{


    int numChannels = inBuffer.getNumChannels();
    int numSamples  = inBuffer.getNumSamples();
    outBuffer->setSize (numChannels, numSamples);

    // Set desired parameters for the triangle wave
    float frequency = 440.0f;  // fundamental frequency (Hz)
    float amplitude = 0.5f;    // amplitude (0.0 to 1.0)
    float phase = 0.0f;        // initial phase
    float phaseIncrement = frequency / sampleRate;

    for (int sample = 0; sample < numSamples; ++sample)
    {
        float currentPhase = std::fmod (phase, 1.0f);
        float triValue     = generateTriangleSample (currentPhase);
        float sampleValue  = amplitude * triValue;

        // Write this sample to all channels
        for (int channel = 0; channel < numChannels; ++channel)
        {
            float* channelWritePtr = outBuffer->getWritePointer (channel);
            channelWritePtr[sample] = sampleValue;
        }

        phase += phaseIncrement;
    }
}

int readSoundFile (juce::AudioBuffer<float>* buffer)
{
    // Prompt for input file path
    std::cout << "Enter the path to the wave file to process: ";
    std::string filePath;
    std::getline(std::cin, filePath);
    juce::File file (filePath);

    // Create an AudioFormatManager and register basic formats
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create a reader for the given file
    std::unique_ptr<juce::AudioFormatReader> reader (formatManager.createReaderFor(file));
    if (reader)
    {
        // Allocate buffer to the size of the file
        buffer->setSize ((int) reader->numChannels,
                         (int) reader->lengthInSamples);

        // Read samples from the file into the buffer
        bool success = reader->read (buffer,
                                     0,
                                     (int) reader->lengthInSamples,
                                     0,
                                     true,
                                     true);

        if (success)
            return static_cast<int> (reader->sampleRate);

        std::cout << "Failed to copy samples into the buffer from the source wave file.\n";
        return 0;
    }

    std::cout << "Failed to read the source wave file.\n";
    return 0;
}

int writeSoundFile (juce::AudioBuffer<float> buffer, float sampleRate)
{
    // Prompt for output file path
    std::cout << "Enter the path to the wave file to save: ";
    std::string filePath;
    std::getline(std::cin, filePath);
    juce::File file (filePath);

    // Create an AudioFormatManager and register basic formats
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create a writer (WAV)
    std::unique_ptr<juce::AudioFormatWriter> writer (
        formatManager.findFormatForFileExtension("wav")->createWriterFor (
            new juce::FileOutputStream(file),
            sampleRate,
            buffer.getNumChannels(),
            16,
            {},
            0)
    );

    if (writer)
    {
        bool success = writer->writeFromAudioSampleBuffer (buffer, 0, buffer.getNumSamples());
        if (success)
            return 0;

        std::cout << "Failed to write samples to the destination wave file.\n";
        return 1;
    }

    std::cout << "Failed to create a writer for the destination file.\n";
    return 1;
}
