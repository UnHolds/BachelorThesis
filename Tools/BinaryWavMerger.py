
file_1 = "../Code/AudioBuffer/audio_binary/SultansOfSwing.bwav"
file_2 = "../Code/AudioBuffer/audio_binary/CacciatoreDellaNotte.bwav"
file_3 = "../Code/AudioBuffer/audio_binary/CantinaBand.bwav"
file_4 = "../Code/AudioBuffer/audio_binary/NeverGonnaGiveYouUp.bwav"
file_5 = "../Code/AudioBuffer/audio_binary/TheImperialMarch.bwav"

files = [file_1, file_2, file_3, file_4, file_5]
opend_files = []
for f in files:
    opend_files.append(open(f, "rb"))


new_file = [val for tup in zip(*list(map(lambda x: x.read(), opend_files))) for val in tup]

with open("output.bwav", "wb") as f_o:
            f_o.write(bytes(new_file))

for f in opend_files:
    f.close()