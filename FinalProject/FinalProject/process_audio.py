import os
#This point the location, make sure the file won't miss or can't find it
base = "/home/lishi/Desktop/Synth/"
mp3 = base + "my_song.mp3"
wav = base + "my_song.wav"
#show in the main.cpp that the signal had been go thought python
print("🎧 Creating audio effects...")

# Convert to stereo WAV
os.system(f'sox "{mp3}" -r 44100 -b 16 -c 2 "{wav}"')

# Lower pitch version
os.system(f'sox "{wav}" "{base}my_song_lower.wav" pitch -300')

# Pitch shift up
os.system(f'sox "{wav}" "{base}my_song_pitch.wav" pitch 400')

# Distortion
os.system(f'sox "{wav}" "{base}my_song_distortion.wav" overdrive 15')

# Combinations
os.system(f'sox "{wav}" "{base}my_song_lower_pitch.wav" pitch -300 pitch 400')
os.system(f'sox "{wav}" "{base}my_song_lower_distortion.wav" pitch -300 overdrive 15')
os.system(f'sox "{wav}" "{base}my_song_pitch_distortion.wav" pitch 400 overdrive 15')
os.system(f'sox "{wav}" "{base}my_song_lpd.wav" pitch -300 pitch 400 overdrive 15')

print("✅ All audio files are ready.")
