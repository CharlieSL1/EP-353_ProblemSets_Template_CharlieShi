#Final Project Proposal

Charlie Shi EP-353 Final Project

##Project Title

### _(Imprisoned) – Interactive Laser Harp Synthesizer_


##Project Description

For my final project, I propose to build a simple but visually captivating interactive laser-based synthesizer using a Raspberry Pi Compute Module 5 (CM5). The project will consist of a circular array of low-power laser diodes forming a "curtain" or "harp" of light beams around the user, who sits or stands in the center.

Each laser beam will have a corresponding light-sensitive sensor (photoresistor or photodiode). When a user interrupts one of these beams with their hand, the system detects the interruption and triggers the playback of a musical note or audio sample, creating an intuitive and engaging musical experience.

The synthesizer will be programmed in Python, C or C++ leveraging the GPIO pins of the Raspberry Pi CM5. Audio playback will be managed through the PyGame or PyAudio libraries or JUCE, allowing rapid and seamless interaction.

##Technical Components

Raspberry Pi Compute Module 5 Dev Kit

Laser Diodes (650nm red laser, safe 5mW)

Photoresistors or Photodiodes

Resistors and Breadboard

GPIO wiring (jumper cables)

USB Audio Output (Speakers/Headphones)

##Reason for Choosing this Project

I chose this project because it combines audio programming, physical computing, and interactive design into an exciting visual and auditory experience. It applies concepts learned in class, such as GPIO control, audio synthesis, and interactive systems, into a creative and engaging project.

##Anticipated Challenges

Aligning and calibrating laser beams precisely

Handling ambient light interference

Ensuring reliable and responsive audio triggering

##What I Hope to Achieve

By completing this project, I aim to demonstrate a solid understanding of audio programming, interactive hardware integration, and user-centered design. Additionally, I hope to create an interactive installation piece suitable for public demonstration and personal portfolio presentation.

##Timeline

Week 1: Purchase and set up components; complete GPIO input/output setup and basic sensor detection logic.

Week 2 (before class): Implement audio playback triggered by sensors, calibrate laser alignment and sensor sensitivity; finalize design and documentation.