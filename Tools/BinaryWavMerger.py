
file_1 = "../Code/AudioBuffer/audio_binary/SultansOfSwing.bwav"
file_2 = "../Code/AudioBuffer/audio_binary/CacciatoreDellaNotte.bwav"

with open(file_1, "rb") as f1:
    with open(file_2, "rb") as f2:
        new_file = [val for pair in zip(f1.read(), f2.read()) for val in pair]
        with open("output.bwav", "wb") as f_o:
            f_o.write(bytes(new_file))
