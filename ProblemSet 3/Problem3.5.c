//This code defines a structure to store multiple MIDI notes and prints out each of their properties.
#include <stdio.h>

typedef struct {
    int pitch;
    int velocity;
    int channel;
} MIDINote;

void print_notes(MIDINote notes[], int size) {
    for (int i = 0; i < size; i++) {
        printf("The MIDI note has pitch %d, velocity %d, and channel %d.\n",
               notes[i].pitch, notes[i].velocity, notes[i].channel);
    }
}

int main(void) {
    int size;

    printf("How many MIDI notes do you want to enter? ");
    scanf("%d", &size);

    MIDINote notes[size];

    //Use a loop to get pitch, velocity, and channel input for each MIDI note.
    for (int i = 0; i < size; i++) {
        printf("Enter pitch, velocity, and channel for note %d (separated by spaces): ", i + 1);
        scanf("%d %d %d", &notes[i].pitch, &notes[i].velocity, &notes[i].channel);
    }

    //Call the function
    print_notes(notes, size);

    return 0;
}
