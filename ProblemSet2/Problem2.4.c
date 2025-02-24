#include <stdio.h>

// Extend the program from problem 2.3 to also determine the note name (C, C#, D, D#, E, F, F#, G, G#, A, A#, B) of the entered MIDI pitch.
// The note name can be calculated as note = pitch % 12.
// Implement this using a switch statement.
// Print both the note name and octave together to the terminal.
// The printout must look as below when the user enters a MIDI pitch 61:
// The MIDI pitch 61 is C#4.
// Hint:
// Read chapter 0.7.5 in the Audio Programming Book.
// Make use of multiple printf functions to construct the sentence.

int main(){
    int p;
    printf("please enter a value between 0-127: \n");
    scanf("%d", &p);
    if(p >= 0 && p <= 127){
        int octave = p / 12 - 1;
        int note = p % 12;
        char *notename;

        switch (note)
        {
        case 0:
            notename = "C";
            break;
        case 1:
            notename = "C#";
            break;
        case 2:
            notename = "D";
            break;
        case 3:
            notename = "D#";
            break;        
        case 4:
            notename = "E";
            break;
        case 5:
            notename = "F";
            break;
        case 6:
            notename = "F#";
            break;
        case 7:
            notename = "G";
            break;
        case 8:
            notename = "G#";
            break;
        case 9:
            notename = "A";
            break;
        case 10:
            notename = "A#";
            break;
        case 11:
            notename = "B";
            break;        
        default:
            notename = "0";
            break;
        }
        printf("The MIDI pitch %d is %s%d.\n", p, notename, octave);
    }
    else{
        printf("Invalid MIDI pitch. It should be between 0 and 127.\n");
    }
    return 0;
}