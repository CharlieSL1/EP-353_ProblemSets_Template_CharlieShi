#include <stdio.h>
#include <math.h>

void midi_to_freqency(int note){
    double frequency;
    frequency = 440.0 * pow(2.0,(note - 69)/ 12.0);
    printf("The frequency of MIDI note %d is %1.2f Hz.", note, frequency);
}

int main(void){
    int note;
    printf("Please enter a MIDI note: ");
    printf("\n");
    scanf("%d", &note);
    midi_to_freqency(note);
    return 0;
    }
