import math
import matplotlib.pyplot as plt
from scipy import signal

sample_rate = 44100 #Hz
signal_frequency = 2000 #Hz
time = 1/2000 * 2 #sec
amplitude = 1.5
offset = 2.5

def sin_wave(x):
    return math.sin(2 * math.pi * (x / (sample_rate / signal_frequency))) * amplitude + offset

def triangle_wave(x):
    return signal.sawtooth(2 * math.pi * (x / (sample_rate / signal_frequency)), 0.5) * amplitude + offset

def sawtooth_wave(x):
    return signal.sawtooth(2 * math.pi * (x / (sample_rate / signal_frequency)), 1) * amplitude + offset

def get_time_array():
    return list(map(lambda x: x/sample_rate, range(0, round(time * sample_rate))))

def get_signal_array(fun):
    return list(map(fun, range(0, round(time * sample_rate))))


def show_plot():
    plt.plot(get_time_array(), get_signal_array(sin_wave))
    plt.plot(get_time_array(), get_signal_array(triangle_wave))
    plt.plot(get_time_array(), get_signal_array(sawtooth_wave))
    plt.show()

def voltage_to_binary(voltage):
    return int(255 * voltage / 4.096)

def print_header_file(function):
    header_data = """
#ifndef AUDIO_DATA_H
#define AUDIO_DATA_H

#include "stdint.h"

ECALPER
uint8_t data[] = {REPLACE};

#endif
"""

    header_data = header_data.replace("REPLACE", ', '.join(map(lambda x:  str(voltage_to_binary(x)), get_signal_array(function))))
    header_data = header_data.replace('ECALPER', 'uint32_t length = ' + str(len(get_signal_array(function))) + ';')

    print(header_data)

print_header_file(triangle_wave)