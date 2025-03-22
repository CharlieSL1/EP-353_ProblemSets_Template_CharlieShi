#include <stdio.h>

typedef struct {
    int pitch;
    int velocity;
    int channel;
} MIDINote;

void transpose_notes(MIDINote* notes, int size, int steps) {
    for (int i = 0; i < size; i++) {
        notes[i].pitch += steps;
    }
}

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

    for (int i = 0; i < size; i++) {
        printf("Enter pitch, velocity, and channel for note %d (separated by spaces): ", i + 1);
        scanf("%d %d %d", &notes[i].pitch, &notes[i].velocity, &notes[i].channel);
    }

    int steps;
    printf("Enter number of steps (0 ~ 11) to transpose the pitch: ");
    scanf("%d", &steps);

    transpose_notes(notes, size, steps);
    print_notes(notes, size);

    return 0;
}
