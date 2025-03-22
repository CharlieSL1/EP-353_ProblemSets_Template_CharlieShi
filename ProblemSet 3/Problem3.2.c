#include <stdio.h>
#include <math.h>

double midi_to_frequency (int note){
    return 440.0 * pow(2.0,(note - 69)/ 12.0);
}

void print_chord_frequencies(int chord[ ], int size){
        for (int i = 0; i < size; i++){
            double frequency = midi_to_frequency(chord[i]);
            printf("The frequency of MIDI note %d is %1.2f Hz.\n", chord[i], frequency);
        }
    }

int main(void){
    int size;
    printf("Please enter how many MIDI notes you want to enter : ");
    printf("\n");
    scanf("%d", &size);

    int chord[size];
    printf("Enter the MIDI notes of the chord (separated by spaces):\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &chord[i]);
    }
    print_chord_frequencies(chord, size);
    return 0;
}