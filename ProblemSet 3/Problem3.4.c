//This code defines a structure to represent a single MIDI note and prints out its properties.
#include <stdio.h>

//Define a structure for MIDI note that stores pitch, velocity, and channel.
typedef struct {
    int pitch;
    int velocity;
    int channel;
} MIDINote;

//Define a print function that takes a MIDINote and prints out its information.
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

    //Call the print function
    print_note(note);

    return 0;
}
