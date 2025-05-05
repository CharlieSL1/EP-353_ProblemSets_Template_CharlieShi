# README.md – Synth Controller Project (EP-353 Final)

## Overview

This project is a real-time hardware-based music effects controller built on a Raspberry Pi. It allows the user to play a music track and apply real-time effects using physical buttons. It includes an LED matrix display to show the current active effects.

You can toggle pitch shift, distortion, and low pitch shift (lower pitch) in real-time using buttons connected to GPIO pins. The system also uses a Python preprocessing script to prepare various effect combinations from a source MP3 file.

## Features

* **Start / Pause Playback** (GPIO 18)
* **Stop Playback** (GPIO 17)
* **Pitch Shift Toggle (+400 cents)** (GPIO 22)
* **Distortion Toggle** (GPIO 13)
* **Lower Pitch Toggle (Pitch -300 cents)** (automatic switch in logic)
* **LED Status Display using MAX7219**

## Hardware Requirements

*Figure: Example wiring layout for buttons and MAX7219 matrix display.*

* Raspberry Pi (any model with GPIO support)
* Buttons connected to GPIO 18, 17, 22, 13
* MAX7219 8x8 LED Matrix
* Breadboard + Jumper Wires

## Software Requirements

* Raspberry Pi OS (Linux)
* `wiringPi` library (installed using build script)
* `sox` command-line audio processor

## How to Set Up

1. Clone this repository into your Raspberry Pi:

   ```bash
   git clone https://github.com/yourusername/FinalProject.git
   cd FinalProject
   ```

2. Make sure `wiringPi` and `sox` are installed:

   ```bash
   sudo apt update
   sudo apt install sox alsa-utils
   git clone https://github.com/WiringPi/WiringPi.git
   cd WiringPi
   ./build
   ```

3. Connect buttons and LED matrix to your Pi using GPIO pins as shown in the diagram (not included here).

4. Place your input MP3 file as `my_song.mp3` in the `FinalProject` folder.

5. Run the Python script to preprocess audio:

   ```bash
   python3 process_audio.py
   ```

6. Compile the main program:

   ```bash
   g++ -o synth synth.cpp -lwiringPi
   ```

7. Run the controller:

   ```bash
   ./synth
   ```

## Using the Synth

* Press the **Start/Pause** button (GPIO 18) to begin playback.
* Use the **Stop** button (GPIO 17) to stop playback.
* Press the **Pitch Shift** button (GPIO 22) to toggle a +400 cents pitch shift.
* Press the **Distortion** button (GPIO 13) to toggle distortion.
* The system logic will automatically use the right `.wav` file based on selected effects.
* Active effects are shown on the MAX7219 LED matrix display.

## Notes

* All audio files are generated using `sox`. Your source MP3 must be clean and stereo.
* If an effect file is missing, playback will fail. Always run the Python script before using.
* The system automatically stops and restarts audio when an effect toggle is changed.

## Troubleshooting

* **Button not working?** Check wiring and use BCM GPIO numbers.
* **No audio?** Ensure `aplay` works by testing a WAV file manually.
* **Missing files?** Rerun `process_audio.py` to regenerate.
* **VERY!VERY!USEFUL!** IT TAKE ME ALL NIGHT TO DEBUG AND COMING OUT WITH THESE USER MANUAL

## Author

Li Shi – Berklee College of Music
EP-353 Final Project, Spring 2025
