#Technical Design Document

## Project Goals

The goal of this project was to design a physical audio controller that gives users a tactile, immediate way to manipulate audio effects on a Raspberry Pi. The system should be intuitive, reliable, and visually informative through hardware feedback like LEDs.

## System Architecture

The project consists of two main components:

1. **C++ Core Controller**: Handles GPIO input, controls playback using `aplay`, and writes effect states to a MAX7219 LED matrix.
2. **Python Preprocessing Script**: Uses SoX to convert an MP3 input file into a set of `.wav` files with pre-baked effects. This avoids real-time processing overhead.

## Button Design & GPIO Mapping

We mapped the buttons to the following GPIO pins using the BCM layout:

* GPIO 18: Start / Pause toggle
* GPIO 17: Stop
* GPIO 22: Pitch shift (+400 cents)
* GPIO 13: Distortion toggle

Buttons use internal pull-up resistors and are read using digitalRead() in a loop with basic edge detection.

## Audio Effects & File Logic

Real-time effects are simulated by pre-rendering every possible combination of three effects:

* Pitch down (lower pitch): `pitch -300`
* Pitch up (static): `pitch +400`
* Distortion: `overdrive 15`

The logic in `main.cpp` uses boolean flags to choose the correct file to play from 8 possible combinations:

* Original
* Lower
* Pitch
* Distortion
* Lower + Pitch
* Lower + Distortion
* Pitch + Distortion
* Lower + Pitch + Distortion

## LED Display Logic

The MAX7219 display shows one character per effect:

* 'L' = Lower Pitch
* 'P' = Pitch
* 'D' = Distortion

The display is updated whenever an effect is toggled using `max7219_write()`.

## Error Handling

* If no file is found, `aplay` fails silently.
* `killall aplay` is used before each playback to prevent overlap.
* Users are instructed to re-run the Python script if audio files are missing.

## Why This Design?

Sometime when we lay on the bed or don't want to move, having a controller that can control the speaker remotely and have DSP function in it, wasn't a cool thing to show off with your friends?

## Future Improvements

* Add volume control knob using ADC
* Replace pre-rendered files with real-time audio processing using C++ DSP
* Add visual spectrum analyzer using FFT and the LED matrix
* Add web-based UI for remote control


