//import necessary libraries
#include <wiringPi.h>
#include <iostream>
#include <string>
#include <array>
#include <ctime>
#include <cstdlib>

//Pin definitions
#define SinPin 0 // GPIO 17
#define SawPin 1 // GPIO 18
#define TriPin 2 // GPIO 27
#define SqrPin 3 // GPIO 22

//Waveform class
class waveform
{
public:
    waveform()
    {
        wiringPiSetup();
        pinMode(SinPin, OUTPUT);
        pinMode(SawPin, OUTPUT);
        pinMode(TriPin, OUTPUT);
        pinMode(SqrPin, OUTPUT);
    }

    void generateWaveform(int waveformType)
    {
        switch (waveformType)
        {
        case 0: // Sine wave
            digitalWrite(SinPin, HIGH);
            delay(1000);
            digitalWrite(SinPin, LOW);
            break;
        case 1: // Sawtooth wave
            digitalWrite(SawPin, HIGH);
            delay(1000);
            digitalWrite(SawPin, LOW);
            break;
        case 2: // Triangle wave
            digitalWrite(TriPin, HIGH);
            delay(1000);
            digitalWrite(TriPin, LOW);
            break;
        case 3: // Square wave
            digitalWrite(SqrPin, HIGH);
            delay(1000);
            digitalWrite(SqrPin, LOW);
            break;
        default:
            std::cerr << "Invalid waveform type" << std::endl;
            break;
        }
    }
};

int main()
{
    waveform myWaveform; // create new item

    myWaveform.generateWaveform(0); // create a sinwave

    return 0;
}
