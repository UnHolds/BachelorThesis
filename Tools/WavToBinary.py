from scipy.io import wavfile

max_amplitude = 1.5
offset = 2.5
path = '../Code/ExperimentI2CSpeakerSystem/audio/CantinaBand60.wav'

samplerate, data = wavfile.read(path)


#scale the data to 8bit / set amplitdue
max_amp = max(max(data), abs(min(data)))

max_set_amp_bit = int(255 * max_amplitude / 4.096)

mult_factor = max_set_amp_bit / max_amp
offset_bit = int(255 * offset / 4.096)

data = list(map(lambda x: int(x * mult_factor) + offset_bit, data))

with open(path.split('/')[-1].replace(".wav", ".bwav"), "wb") as f:
    f.write(bytes(data))

print(list(map(int, data[:1000])))