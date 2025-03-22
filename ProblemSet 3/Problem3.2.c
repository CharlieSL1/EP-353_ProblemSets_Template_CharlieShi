//This Code maintain the function of 3.1 and printing out multi value.
#include <stdio.h>
#include <math.h>
//3.1 function
double midi_to_frequency (int note){
    return 440.0 * pow(2.0,(note - 69)/ 12.0);
}
//print function
void print_chord_frequencies(int chord[ ], int size){
        for (int i = 0; i < size; i++){
            double frequency = midi_to_frequency(chord[i]);
            printf("The frequency of MIDI note %d is %1.2f Hz.\n", chord[i], frequency);
        }
    }

int main(void){
    //set the size of input
    int size;
    printf("Please enter how many MIDI notes you want to enter : ");
    printf("\n");
    scanf("%d", &size);
    //requset for the notes.
    int chord[size];
    printf("Enter the MIDI notes of the chord (separated by spaces):\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &chord[i]);
    }
    //return back the value to function.
    print_chord_frequencies(chord, size);
    return 0;
}