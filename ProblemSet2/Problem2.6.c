#include <stdio.h>
// Write a program that uses nested for-loops to generate a table of musical intervals.
// The outer loop should iterate over the 12 semitones in an octave (from C (0) to B (11)).
// The inner loop should calculate the interval from the note in the outer loop to each note in the octave, using the formula interval = (note2 - note1 + 12) % 12.
// The interval is the number of semitones between the two notes, and it should always be a non-negative number less than 12.
// The interval from a note to itself is 0, and the interval from a note to the next semitone up is 1.
// Print the table of intervals to the console.
// Instead of printing the intervals as numbers from 0 to 11, print them as musical intervals: unison (0), minor second (1), major second (2), minor third (3), major third (4), perfect fourth (5), tritone (6), perfect fifth (7), minor sixth (8), major sixth (9), minor seventh (10), and major seventh (11).
// Implement this using a switch statement.

int main() {
   
    char *intervaln[] = {
        "unison", "minor second", "major second", "minor third", "major third", 
        "perfect fourth", "tritone", "perfect fifth", "minor sixth", "major sixth", 
        "minor seventh", "major seventh"
    };
    
    printf("   ");
    for (int i = 0; i < 12; i++) {
        printf("%4d", i);
    }
    printf("\n");

    for (int n1 = 0; n1 < 12; n1++) {
        printf("%2d |", n1);  
        for (int n2 = 0; n2 < 12; n2++) {
            int interval = (n2 - n1 + 12) % 12;
            printf(" %-15s", intervaln[interval]); 
        }
        printf("\n");
    }
    
    return 0;
}
