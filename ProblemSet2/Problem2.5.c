#include <stdio.h>

int main() {
    int p;
    
    while (1) {
        printf("Please enter a MIDI pitch (0-127) or -1 to quit: ");
        scanf("%d", &p);

        if (p == -1) {
            printf("Exiting program.\n");
            break;
        }

        if (p >= 0 && p <= 127) {
            int octave = p / 12 - 1;
            int note = p % 12;
            char *noteName;

            switch (note) {
                case 0: noteName = "C"; break;
                case 1: noteName = "C#"; break;
                case 2: noteName = "D"; break;
                case 3: noteName = "D#"; break;
                case 4: noteName = "E"; break;
                case 5: noteName = "F"; break;
                case 6: noteName = "F#"; break;
                case 7: noteName = "G"; break;
                case 8: noteName = "G#"; break;
                case 9: noteName = "A"; break;
                case 10: noteName = "A#"; break;
                case 11: noteName = "B"; break;
                default: noteName = "?"; break;
            }
            printf("The MIDI pitch %d is %s%d.\n", p, noteName, octave);
        } else {
            printf("Invalid MIDI pitch. It should be between 0 and 127.\n");
        }
    }
    return 0;
}
