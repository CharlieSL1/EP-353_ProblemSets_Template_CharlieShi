#include <stdio.h>
#include <math.h> 
// Problem 2.3: Conditions
// Create a file named Problem2.3.c.
// Write a program that accepts a MIDI pitch as input and checks if it is within a valid range (0 to 127).
// If the MIDI pitch is in a valid range, determine which octave the pitch belongs to.
// The octave for a given MIDI pitch can be calculated as octave = pitch / 12 - 1.
// If the pitch is not in a valid range, let the user know that the MIDI pitch must be between 0 and 127.
// Print the calculated octave to the terminal.
// Here is an example print output from this program when the MIDI pitch is in a valid range:
// The octave for MIDI pitch 60 is 4.
// Here is an example of print output from this program when the MIDI pitch is not in a valid range:
// Invalid MIDI pitch. It should be between 0 and 127.
int main(){
    int p;
    printf("please enter a value between 0-127: \n");
    scanf("%d", &p);
    if(p >= 0 && p <= 127){
        int octive = p / 12 - 1;
        printf("The octave for MIDI pitch %d is %d.\n", p, octive);
    }
    else{
        printf("Invalid MIDI pitch. It should be between 0 and 127.\n");
    }
    return 0;
}
