import math
import matplotlib.pyplot as plt
from scipy import signal

sample_rate = 10000 #Hz
signal_frequency = 10 #Hz
time = 0.25 #sec
amplitude = 4
offset = 2.5

def sin_wave(x):
    return math.sin(2 * math.pi * (x / (sample_rate / signal_frequency))) * amplitude + (offset - (amplitude / 2))

def triangle_wave(x):
    return signal.sawtooth(2 * math.pi * (x / (sample_rate / signal_frequency)), 0.5) * amplitude + (offset - (amplitude / 2))

def sawtooth_wave(x):
    return signal.sawtooth(2 * math.pi * (x / (sample_rate / signal_frequency)), 1) * amplitude + (offset - (amplitude / 2))

def get_time_array():
    return list(map(lambda x: x/sample_rate, range(0, round(time * sample_rate))))

def get_signal_array(fun):
    return list(map(fun, range(0, round(time * sample_rate))))



plt.plot(get_time_array(), get_signal_array(sin_wave))
plt.plot(get_time_array(), get_signal_array(triangle_wave))
plt.plot(get_time_array(), get_signal_array(sawtooth_wave))
plt.show()