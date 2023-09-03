from scipy.io import wavfile

max_amplitude = 1.5
offset = 2.5

samplerate, data = wavfile.read('../Code/ExperimentI2CSpeakerSystem/audio/PinkPanther30.wav')


#scale the data to 8bit / set amplitdue
max_amp = max(max(data), abs(min(data)))

max_set_amp_bit = int(255 * max_amplitude / 4.096)

mult_factor = max_set_amp_bit / max_amp
offset_bit = int(255 * offset / 4.096)

data = list(map(lambda x: int(x * mult_factor) + offset_bit, data))


def print_header_file(data, sample_rate):
    header_data = """
#ifndef AUDIO_DATA_H
#define AUDIO_DATA_H

#include "stdint.h"

#define SAMPLE_RATE {SAMPLE_RATE}

ECALPER
uint8_t data[] = {REPLACE};

#endif
"""
    header_data = header_data.replace("REPLACE", ', '.join(map(str, data)))
    header_data = header_data.replace('ECALPER', 'uint32_t length = ' + str(len(data)) + ';')
    header_data = header_data.replace('{SAMPLE_RATE}', str(sample_rate))

    print(header_data)

print_header_file(data, samplerate)