/*
  ==============================================================================
    The template DAFx file for Problem 4.5: Noise Gate

    What I do in this code:
      - Reads an input WAV file (noisy.wav).
      - Applies a noise gate with threshold ±0.02.
        (If abs(sample) < 0.02, set sample = 0.0f)
      - Writes the result to noisegate.wav.

    Usage Steps:
      1) Build and run this program in your JUCE project named "Problem4.5".
      2) Enter the path to your input WAV file
      3) Enter the path for your output WAV file 
  ==============================================================================
*/

// This gets generated dynamically by CMake. VSCode may complain it can't
// find it until you generate the CMake build directory
#include <JuceHeader.h>
#include <iostream>

// Function prototypes
int  readSoundFile  (juce::AudioBuffer<float>* buffer);
int  writeSoundFile (juce::AudioBuffer<float> buffer, float sampleRate);
void process        (juce::AudioBuffer<float> inBuffer, 
                     juce::AudioBuffer<float>* outBuffer);

//==============================================================================
int main()
{
    // 1. Read the source file into an input buffer
    juce::AudioBuffer<float> inBuffer;
    float sampleRate = (float) readSoundFile(&inBuffer);

    if (sampleRate <= 0.0f)
    {
        std::cerr << "Error: Failed to read input file.\n";
        return 1;
    }

    // 2. Create an output buffer
    juce::AudioBuffer<float> outBuffer(inBuffer.getNumChannels(),
                                       inBuffer.getNumSamples());

    // 3. Process the audio data (apply noise gate)
    process(inBuffer, &outBuffer);

    // 4. Write the processed audio data to a file
    if (writeSoundFile(outBuffer, sampleRate) != 0)
    {
        std::cerr << "Error: Failed to write output file.\n";
        return 1;
    }

    std::cout << "Noise gate applied successfully.\n";
    return 0;
}

//==============================================================================
// Process function: Applies a noise gate with threshold ±0.02
//==============================================================================
void process (juce::AudioBuffer<float> inBuffer,
              juce::AudioBuffer<float>* outBuffer)
{
    const float threshold = 0.02f;

    // Make sure outBuffer has the same size as inBuffer
    outBuffer->setSize(inBuffer.getNumChannels(), inBuffer.getNumSamples());

    // Iterate through each sample in each channel
    for (int channel = 0; channel < inBuffer.getNumChannels(); ++channel)
    {
        const float* inPtr  = inBuffer.getReadPointer(channel);
        float*       outPtr = outBuffer->getWritePointer(channel);

        for (int i = 0; i < inBuffer.getNumSamples(); ++i)
        {
            float sampleVal = inPtr[i];
            if (std::fabs(sampleVal) < threshold)
                outPtr[i] = 0.0f;   // Attenuate to zero
            else
                outPtr[i] = sampleVal;
        }
    }
}

//==============================================================================
// This function reads the audio data from a given WAV file into an AudioBuffer
//==============================================================================
int readSoundFile (juce::AudioBuffer<float>* buffer)
{
    std::cout << "Enter the path to the wave file (e.g., noisy.wav): ";
    std::string filePath;
    std::getline(std::cin, filePath);

    juce::File file(filePath);

    // Create an AudioFormatManager and register basic formats (WAV, AIFF, etc.)
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create a unique_ptr to manage the reader
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
    if (reader == nullptr)
    {
        std::cerr << "Error: Could not open file " << filePath << "\n";
        return 0;
    }

    // Resize the buffer to fit the entire length of the file
    buffer->setSize((int)reader->numChannels, (int)reader->lengthInSamples);

    // Read samples from the file into the buffer
    bool success = reader->read(buffer,          // destination buffer
                                0,               // destination start sample
                                (int)reader->lengthInSamples,  // samples to read
                                0,               // start sample in file
                                true,            // use left channel
                                true);           // use right channel

    if (!success)
    {
        std::cerr << "Error: Failed to read samples into the buffer.\n";
        return 0;
    }

    // Return sample rate if successful
    return (int) reader->sampleRate;
}

//==============================================================================
// This function writes the audio data from a given AudioBuffer to a WAV file
//==============================================================================
int writeSoundFile (juce::AudioBuffer<float> buffer, float sampleRate)
{
    std::cout << "Enter the path to save the output wave file (e.g., noisegate.wav): ";
    std::string filePath;
    std::getline(std::cin, filePath);

    juce::File file (filePath);

    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create an output stream
    std::unique_ptr<juce::FileOutputStream> outStream (file.createOutputStream());
    if (outStream == nullptr)
    {
        std::cerr << "Error: Could not create output stream for file " << filePath << "\n";
        return 1;
    }

    // Use WavAudioFormat to write a WAV file
    juce::WavAudioFormat wavFormat;
    std::unique_ptr<juce::AudioFormatWriter> writer (
        wavFormat.createWriterFor(outStream.get(),            // output stream
                                  sampleRate,                 // sample rate
                                  (unsigned int) buffer.getNumChannels(),
                                  16,                         // bits per sample
                                  {},                         // metadata
                                  0)
    );

    if (writer == nullptr)
    {
        std::cerr << "Error: Could not create WAV writer.\n";
        return 1;
    }

    // Now that the writer owns the stream, release our unique_ptr
    outStream.release();

    // Write the entire buffer
    writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());

    return 0;
}
