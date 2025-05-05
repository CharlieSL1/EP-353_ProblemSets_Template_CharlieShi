#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

// SPI config for MAX7219
#define SPI_CHANNEL 0
#define SPI_SPEED   1000000

// GPIO buttons (BCM numbering)
#define BTN_START   18
#define BTN_STOP    17
#define BTN_PITCH   22
#define BTN_DIST    13

// File paths
// ___ALL the File in Raspberry Pi System______
const std::string BASE = "/home/lishi/Desktop/Synth/";
const std::string ORIG = BASE + "my_song.wav";
const std::string LOW  = BASE + "my_song_lower.wav";
const std::string PIT  = BASE + "my_song_pitch.wav";
const std::string DIST = BASE + "my_song_distortion.wav";
const std::string LP   = BASE + "my_song_lower_pitch.wav";
const std::string LD   = BASE + "my_song_lower_distortion.wav";
const std::string PD   = BASE + "my_song_pitch_distortion.wav";
const std::string LPD  = BASE + "my_song_lpd.wav";

// State variables
bool lower_on = false;
bool pitch_on = false;
bool distortion_on = false;
bool is_playing = false;

// MAX7219 display
// I learn this from this website 
// https://docs.sunfounder.com/projects/raphael-kit/en/latest/python/1.1.6_led_dot_matrix_python.html

void max7219_write(unsigned char address, unsigned char data) {
    unsigned char buffer[2] = {address, data};
    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 2);
}

void max7219_init() {
    max7219_write(0x09, 0x00);
    max7219_write(0x0A, 0x03);
    max7219_write(0x0B, 0x07);
    max7219_write(0x0C, 0x01);
    max7219_write(0x0F, 0x00);
    for (int i = 1; i <= 8; i++) max7219_write(i, 0x00);
}

void display_status() {
    for (int i = 1; i <= 8; i++) max7219_write(i, 0x00);
    if (lower_on)      max7219_write(1, 0b01001100); // 'L'
    if (pitch_on)      max7219_write(2, 0b01010000); // 'P'
    if (distortion_on) max7219_write(3, 0b01000100); // 'D'
}


// Playback control
void stop_music() {
    system("killall aplay > /dev/null 2>&1");
    is_playing = false;
}

void play_music() {
    stop_music();
    std::string path = ORIG;
    //this part using the C++ if logic I mention in the Presentation
    if (lower_on && pitch_on && distortion_on) path = LPD;
    else if (lower_on && pitch_on)             path = LP;
    else if (lower_on && distortion_on)        path = LD;
    else if (pitch_on && distortion_on)        path = PD;
    else if (lower_on)                         path = LOW;
    else if (pitch_on)                         path = PIT;
    else if (distortion_on)                    path = DIST;
    std::string command = "aplay \"" + path + "\" &";
    system(command.c_str());
    // resign the active status
    is_playing = true;
}

// Optional preprocessing
// Look more professional :)
void preprocess_audio_files() {
    printf(" Running Python script to prepare audio files...\n");
    system("python3 /home/lishi/Desktop/Synth/process_audio.py");
    printf(" Audio files ready.\n");
}

// Button actions
// This set up the BTN for Start and Paused
void handle_start_pause() {
    if (is_playing) {
        stop_music();
        printf("⏸️ Paused.\n");
    } else {
        play_music();
        printf("▶️ Playing.\n");
    }
}

// This set up the BTN to Stop
void handle_stop() {
    stop_music();
    printf("⏹️ Stopped.\n");
}
// This set the pitch shift BTN
void handle_pitch() {
    pitch_on = !pitch_on;
    printf("🎵 Pitch is now %s\n", pitch_on ? "ON" : "OFF");
    display_status();
    if (is_playing) play_music();
}
// This set up the distortion BTN
void handle_distortion() {
    distortion_on = !distortion_on;
    printf("🔥 Distortion is now %s\n", distortion_on ? "ON" : "OFF");
    display_status();
    if (is_playing) play_music();
}
// This set up the Pitch lower BTN
void handle_lower_pitch() {
    lower_on = !lower_on;
    printf("🔻 Lower pitch is now %s\n", lower_on ? "ON" : "OFF");
    display_status();
    if (is_playing) play_music();
}

// Main Function
int main() {
    //Just for a Breakpoint like output for essier debug
    if (wiringPiSetupGpio() == -1 || wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1) {
        printf("Error: Could not initialize GPIO or SPI.\n");
        return 1;
    }
    //GPIO PINMODE SETTING
    pinMode(BTN_START, INPUT);
    pinMode(BTN_STOP, INPUT);
    pinMode(BTN_PITCH, INPUT);
    pinMode(BTN_DIST, INPUT);
    //GPIO UP and down setup
    pullUpDnControl(BTN_START, PUD_UP);
    pullUpDnControl(BTN_STOP, PUD_UP);
    pullUpDnControl(BTN_PITCH, PUD_UP);
    pullUpDnControl(BTN_DIST, PUD_UP);

    //call function
    max7219_init();
    display_status();
    preprocess_audio_files();
    play_music();
    //Start signal
    printf("🎛 Synth controller started.\n");

    //Look at the status 
    bool last_start = HIGH, last_stop = HIGH, last_pitch = HIGH, last_dist = HIGH;
    //Keep the BTN function working
    while (true) {
        /
        int cur_start = digitalRead(BTN_START);
        int cur_stop  = digitalRead(BTN_STOP);
        int cur_pitch = digitalRead(BTN_PITCH);
        int cur_dist  = digitalRead(BTN_DIST);

        if (cur_start == LOW && last_start == HIGH) handle_start_pause();
        if (cur_stop  == LOW && last_stop  == HIGH) handle_lower_pitch();
        if (cur_pitch == LOW && last_pitch == HIGH) handle_pitch();
        if (cur_dist  == LOW && last_dist == HIGH)  handle_distortion();

        last_start = cur_start;
        last_stop  = cur_stop;
        last_pitch = cur_pitch;
        last_dist  = cur_dist;

        delay(100);
    }

    return 0;
}
