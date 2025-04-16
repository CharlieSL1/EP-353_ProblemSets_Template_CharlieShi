/*
  ==============================================================================

    What I do for this code:
      1. Create a JUCE project named "Problem4.6" using the DAFxTemplate (or similar).
      2. Replace the main processing logic with the code below.
      3. Build and run; when prompted, enter:
         - Path to "sine.wav" (must be a 16-bit WAV).
         - Desired number of bits to keep (1..16).
         - Output path (e.g. "reduct.aiff").

    Explanation of steps:
      - The file is read via AudioFormatReader, which returns floats in [-1..1].
      - We convert each float sample to a 16-bit short in [-32768..32767].
      - We call keep_bits_from_16(), which masks out (16 - keepBits) bits.
      - We convert the result back to float in [-1..1].
      - Finally, we write the data as a 24-bit AIFF file named "reduct.aiff".

  ==============================================================================
*/

#include <JuceHeader.h>
#include <iostream>
#include <cmath>

//==============================================================================
/** 
    keep_bits_from_16:
    - input:  a 16-bit signed PCM sample in the range [-32768..32767]
    - keepBits: how many of the top bits to keep 
    - use the knowalege in office hour!
*/
short keep_bits_from_16 (short input, int keepBits)
{
    if (keepBits >= 16)
        return input;         // Keep all bits if keepBits = 16
    if (keepBits < 1)
        keepBits = 1;         // Minimum of 1 bit

    // Create a mask that retains the top 'keepBits' bits
    // e.g. if keepBits=4, then mask = 0xFFFF << (16 - 4) = 0xFFFF << 12
    unsigned int mask = 0xFFFFu << (16 - keepBits);

    // Apply mask
    short output = static_cast<short> (input & mask);
    return output;
}

//==============================================================================
// Forward declarations for DAFxTemplate-style functions
int readSoundFile  (juce::AudioBuffer<float>* buffer);
int writeSoundFile (const juce::AudioBuffer<float>& buffer, double sampleRate);
void process       (const juce::AudioBuffer<float>& inBuffer,
                    juce::AudioBuffer<float>* outBuffer,
                    int keepBits);

//==============================================================================
int main()
{
    // 1. Read the input file (sine.wav) into a float buffer
    juce::AudioBuffer<float> inBuffer;
    double sampleRate = readSoundFile (&inBuffer);
    if (sampleRate <= 0.0)
    {
        std::cerr << "Error: Failed to open input file or invalid sample rate.\n";
        return 1;
    }

    // Prompt user for how many bits to keep
    std::cout << "Enter keepBits in [1..16]: ";
    int keepBits = 16;
    std::cin >> keepBits;
    // Clear leftover newline from buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // 2. Create an output buffer
    juce::AudioBuffer<float> outBuffer (inBuffer.getNumChannels(),
                                        inBuffer.getNumSamples());

    // 3. Process: do bit reduction
    process (inBuffer, &outBuffer, keepBits);

    // 4. Write the processed data to a 24-bit AIFF file
    if (writeSoundFile (outBuffer, sampleRate) != 0)
    {
        std::cerr << "Error: Failed to write output file.\n";
        return 1;
    }

    std::cout << "Bit reduction complete. Check your reduct.aiff file.\n";
    return 0;
}

//==============================================================================
// process() function:
//  Convert float->short, call keep_bits_from_16(), convert back to float
//==============================================================================
void process (const juce::AudioBuffer<float>& inBuffer,
              juce::AudioBuffer<float>* outBuffer,
              int keepBits)
{
    int numChannels = inBuffer.getNumChannels();
    int numSamples  = inBuffer.getNumSamples();

    outBuffer->setSize(numChannels, numSamples);

    for (int ch = 0; ch < numChannels; ++ch)
    {
        const float* inPtr  = inBuffer.getReadPointer(ch);
        float*       outPtr = outBuffer->getWritePointer(ch);

        for (int i = 0; i < numSamples; ++i)
        {
            // 1) Convert float [-1..1] to short [-32768..32767]
            float inSample = inPtr[i];
            if (inSample > 1.0f)  inSample = 1.0f;
            if (inSample < -1.0f) inSample = -1.0f;

            short sVal = (short) juce::roundToInt (inSample * 32767.0f);

            // 2) Apply bit reduction
            short reduced = keep_bits_from_16(sVal, keepBits);

            // 3) Convert back to float
            //    (We store in [-1..1] range. Div by 32767.0 is a common approximation.)
            float outSample = static_cast<float>(reduced) / 32767.0f;

            outPtr[i] = outSample;
        }
    }
}

//==============================================================================
// readSoundFile: read from user-specified path into a float AudioBuffer.
// We expect a 16-bit PCM WAV. 
//==============================================================================
int readSoundFile (juce::AudioBuffer<float>* buffer)
{
    std::cout << "Enter path to the 16-bit sine.wav file: ";
    std::string inPath;
    std::getline(std::cin, inPath);

    juce::File inFile (inPath);
    if (! inFile.existsAsFile())
    {
        std::cerr << "File does not exist: " << inPath << "\n";
        return 0;
    }

    // Create a format manager and register basic formats
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    // Create an AudioFormatReader
    std::unique_ptr<juce::AudioFormatReader> reader (formatManager.createReaderFor (inFile));
    if (reader == nullptr)
    {
        std::cerr << "Failed to create reader for file: " << inPath << "\n";
        return 0;
    }

    // Ideally check if it's 16-bit
    if (reader->bitsPerSample != 16)
    {
        std::cerr << "Warning: This file is not 16-bit PCM, behavior may differ.\n";
    }

    // Allocate buffer memory
    buffer->setSize ((int) reader->numChannels,
                     (int) reader->lengthInSamples);

    // Read the entire file
    bool ok = reader->read (buffer,                // dest buffer
                            0,                     // startSample in dest
                            (int) reader->lengthInSamples,
                            0,                     // startSample in source
                            true,                  // use left
                            true);                 // use right
    if (!ok)
    {
        std::cerr << "Error reading samples.\n";
        return 0;
    }

    return (int) reader->sampleRate;  // cast sampleRate to int for convenience
}

//==============================================================================
// writeSoundFile: write out as 24-bit AIFF to demonstrate final effect
//==============================================================================
int writeSoundFile (const juce::AudioBuffer<float>& buffer, double sampleRate)
{
    std::cout << "Enter path for the output (e.g. reduct.aiff): ";
    std::string outPath;
    std::getline(std::cin, outPath);

    juce::File outFile (outPath);

    if (auto outStream = outFile.createOutputStream())
    {
        // We choose AIFF, 24-bit
        juce::AiffAudioFormat aiffFormat;
        std::unique_ptr<juce::AudioFormatWriter> writer (
            aiffFormat.createWriterFor (outStream.get(),
                                        sampleRate,
                                        buffer.getNumChannels(),
                                        24,    // 24 bits per sample
                                        {},
                                        0)
        );

        if (writer != nullptr)
        {
            outStream.release(); // pass ownership to writer
            writer->writeFromAudioSampleBuffer (buffer, 0, buffer.getNumSamples());
            return 0;
        }
        else
        {
            std::cerr << "Failed to create AIFF writer.\n";
            return 1;
        }
    }
    std::cerr << "Failed to create output stream.\n";
    return 1;
}
