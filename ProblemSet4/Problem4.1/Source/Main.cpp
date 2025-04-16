#include <JuceHeader.h>
#include <iostream>

// Function prototypes
bool readSoundFile(juce::AudioBuffer<float>& buffer, double& sampleRate);
bool writeSoundFile(const juce::AudioBuffer<float>& buffer, double sampleRate, const juce::File& outFile);
void process(const juce::AudioBuffer<float>& inBuffer, juce::AudioBuffer<float>& outBuffer);

//==============================================================================
int main(){
    AudioFormatManager formatmanager;
    formatmanager.registerBasicFormats();
    std::unique_ptr<AudioFormatReader> reader(formatmanager.createReaderFor(File("SN.wav")));
    if (reader == nullptr){
        std::cerr << "failed to load file " << std::endl;
        return -1;
    }
    AudioBuffer <float> buffer(reader->numChannels,reader->lengthInSamples);
    reader->read(&buffer,0,reader->lengthInSamples,0,true,true);
    //reverse Smaple
    for(int channel = 0; channel < buffer.getNumChannels();channel++){
        buffer.reverse(channel,0,buffer.getNumSamples());
    }
    // Write Reverse audio to a file
    std::unique_ptr<AudioFormatWriter> writer(formatmanager.findFormatForFileExtension("wav")->
    createWriterFor(
        new FileOutputStream(File("Reverse_SN.wav")),
        reader->sampleRate,
        buffer.getNumChannels(),
        reader->bitsPerSample,
        {},0));
        if(writer != nullptr){
            writer->writeFromAudioSampleBuffer(buffer,0,buffer.getNumSamples());

        }
        else{
            std::cerr << "failed to write the reverse audio file " << std::endl;
            return -1;
        }
        std::cout << "reverse audio create sussefully"<< std::endl;
        return 0;
    
}

bool readSoundFile(juce::AudioBuffer<float>& buffer, double& sampleRate)
{
    juce::File file = juce::File::getCurrentWorkingDirectory().getChildFile("SN.wav");

    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));

    if (reader != nullptr)
    {
        buffer.setSize(reader->numChannels, static_cast<int>(reader->lengthInSamples));
        if (reader->read(&buffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true))
        {
            sampleRate = reader->sampleRate;
            return true;
        }
    }

    std::cout << "Error reading SN.wav\n";
    return false;
}

bool writeSoundFile(const juce::AudioBuffer<float>& buffer, double sampleRate, const juce::File& outFile)
{
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    std::unique_ptr<juce::FileOutputStream> stream(outFile.createOutputStream());
    if (!stream)
    {
        std::cout << "Failed to create output stream\n";
        return false;
    }

    juce::WavAudioFormat wavFormat;
    std::unique_ptr<juce::AudioFormatWriter> writer(wavFormat.createWriterFor(stream.get(), sampleRate, buffer.getNumChannels(), 16, {}, 0));

    if (writer != nullptr)
    {
        stream.release(); // writer now owns the stream
        return writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
    }

    std::cout << "Failed to write ReverseSN.wav\n";
    return false;
}
