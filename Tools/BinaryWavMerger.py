
file_1 = r"bass.bwav"
file_2 = r"drums.bwav"
file_3 = r"guitar.bwav"
file_4 = r"piano_organ.bwav"
file_5 = r"vox.bwav"

files = [file_1, file_2, file_3, file_4, file_5]
opend_files = []
for f in files:
    opend_files.append(open(f, "rb"))



## file format
#{song_num}_{mode}_{name}.bwav

new_file = [val for tup in zip(*list(map(lambda x: x.read(), opend_files))) for val in tup]

output_file = f'00_{2 if len(files) > 1 else 1}_output.bwav'


with open(output_file, "wb") as f_o:
            f_o.write(bytes(new_file))

for f in opend_files:
    f.close()
