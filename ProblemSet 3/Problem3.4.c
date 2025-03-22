#include <stdio.h>

typedef struct {
    int pitch;
    int velocity;
    int channel;
} MIDINote;


void print_note(MIDINote note) {
    printf("The MIDI note has pitch %d, velocity %d, and channel %d.\n", note.pitch, note.velocity, note.channel);
}

int main(void) {
    MIDINote note;

    printf("Enter pitch: ");
    scanf("%d", &note.pitch);

    printf("Enter velocity: ");
    scanf("%d", &note.velocity);

    printf("Enter channel: ");
    scanf("%d", &note.channel);

    print_note(note);

    return 0;
}
