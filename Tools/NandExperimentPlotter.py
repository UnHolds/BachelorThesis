import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button
import sys
from tkinter.filedialog import askopenfilename
import numpy as np

nargs = len(sys.argv)

filename = ""

if nargs == 1:
    filename = askopenfilename()
else:
    filename = sys.argv[0]

header = []
vOut5V = {}
vOutDac = {}
vInput = []
vVccDac = {}
with open(filename) as f:
    lines = f.readlines()
    header = ["VCC Bit", "Measured VCC", "Input Bit", "Measured Input", "Measured V-Out 5V", "Measured V-Out DAC"]
    #parse data
    preData = list(map(lambda x: list(map(float, x.split(';'))), lines))
    for i in range(128, 256):
        vOut5V[i] = list(map(lambda x: x[4], list(filter(lambda a: a[0] == i, preData))))
        vOutDac[i] = list(map(lambda x: x[5], list(filter(lambda a: a[0] == i, preData))))
        if i == 128:
            vInput = list(map(lambda x: x[3], list(filter(lambda a: a[0] == i, preData))))
        vVccDac[i] = list(map(lambda x: x[1], list(filter(lambda a: a[0] == i, preData))))[0]

# The parametrized function to be plotted
def getVout5V(vccBit):
    return vOut5V[vccBit]

def getVoutDac(vccBit):
    return vOutDac[vccBit]



# Create the figure and the line that we will manipulate
fig, ax = plt.subplots()
line5V, = ax.plot(vInput, getVout5V(255), lw=2)
lineDac, = ax.plot(vInput, getVoutDac(255), lw=2)
ax.set_xlabel('Input [V]')
ax.set_ylabel('Output [V]')
vccDacText = ax.text(3, 5, 'VCC DAC [V]:' + str(vVccDac[255]))

# adjust the main plot to make room for the sliders
fig.subplots_adjust(left=0.25, bottom=0.25)

# Make a horizontal slider to control the frequency.
axfreq = fig.add_axes([0.25, 0.1, 0.65, 0.03])
vcc_slider = Slider(
    ax=axfreq,
    label='VCC [Bit]',
    valstep=1,
    valmin=128,
    valmax=255,
    valinit=255,
)


# The function to be called anytime a slider's value changes
def update(val):
    line5V.set_ydata(getVout5V(vcc_slider.val))
    lineDac.set_ydata(getVoutDac(vcc_slider.val))
    vccDacText.set_text('VCC DAC [V]: ' + str(vVccDac[vcc_slider.val]))
    fig.canvas.draw_idle()


# register the update function with each slider
vcc_slider.on_changed(update)



plt.show()