import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button
import sys
from tkinter.filedialog import askopenfilename
import numpy as np

nargs = len(sys.argv)

filename = ""

num_values = 255

if nargs == 1:
    filename = askopenfilename()
else:
    filename = sys.argv[0]

header = []
vOutA = {}
vOutB = {}
vInput = []
vVccDac = {}
with open(filename) as f:
    lines = f.readlines()
    header = ["VCC Bit", "Measured VCC", "Input Bit", "Measured Input", "Measured Out A", "Measured Out B"]
    #parse data
    preData = list(map(lambda x: list(map(float, x.split(';'))), lines))
    for i in range(128, num_values + 1):
        vOutA[i] = list(map(lambda x: x[4], list(filter(lambda a: a[0] == i, preData))))
        vOutB[i] = list(map(lambda x: x[5], list(filter(lambda a: a[0] == i, preData))))
        if i == 128:
            vInput = list(map(lambda x: x[3], list(filter(lambda a: a[0] == i, preData))))
        vVccDac[i] = list(map(lambda x: x[1], list(filter(lambda a: a[0] == i, preData))))[0]

# The parametrized function to be plotted
def getVoutA(vccBit):
    return vOutA[vccBit]

def getVoutB(vccBit):
    return vOutB[vccBit]



# Create the figure and the line that we will manipulate
fig, ax = plt.subplots()
lineOutputA, = ax.plot(vInput, getVoutA(num_values), lw=2)
lineOutputB, = ax.plot(vInput, getVoutB(num_values), lw=2)
lineInput, = ax.plot(vInput, vInput, lw=2)
ax.set_xlabel('Input [V]')
ax.set_ylabel('Output [V]')
vccDacText = ax.text(3, 5.2, 'VCC DAC [V]:' + str(vVccDac[num_values]))

# adjust the main plot to make room for the sliders
fig.subplots_adjust(left=0.25, bottom=0.25)

# Make a horizontal slider to control the frequency.
axfreq = fig.add_axes([0.25, 0.1, 0.65, 0.03])
vcc_slider = Slider(
    ax=axfreq,
    label='VCC [Bit]',
    valstep=1,
    valmin=128,
    valmax=num_values,
    valinit=num_values,
)


# The function to be called anytime a slider's value changes
def update(val):
    lineOutputA.set_ydata(getVoutA(vcc_slider.val))
    lineOutputB.set_ydata(getVoutB(vcc_slider.val))
    vccDacText.set_text('VCC DAC [V]: ' + str(vVccDac[vcc_slider.val]))
    fig.canvas.draw_idle()


# register the update function with each slider
vcc_slider.on_changed(update)

lineOutputA.set_label("Output A")
lineOutputB.set_label("Output B")
lineInput.set_label("Input")
ax.legend()


plt.show()
