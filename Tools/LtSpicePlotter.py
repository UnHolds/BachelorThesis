import matplotlib.pyplot as plt
import sys
from tkinter.filedialog import askopenfilename



def get_axis_label(header):
    if header[0] == "V":
        return "Voltage [V]"
    elif header[0] == "I":
        return "Current [A]"


nargs = len(sys.argv)

filename = ""

if nargs == 1:
    filename = askopenfilename()
else:
    filename = sys.argv[0]

data = []
header = []


with open(filename) as f:
    lines = f.readlines()
    header = lines[0].split("\t")
    #parse data
    data = list(map(list,zip(*map(lambda x: list(map(float, x.split("\t"))), lines[1:]))))

    


fig, ax1 = plt.subplots()
ax2 = ax1.twinx()


#check if ms is better
if all(x < 0.1 for x in data[0]):
    data[0] = list(map(lambda x: x*1000, data[0]))
    ax1.set_xlabel('Time [ms]', fontsize=12)
else:
    ax1.set_xlabel('Time [s]', fontsize=12)


secondAxis = False

# plot lines on first axis
for i in range(1, len(header)):
    if header[i][0] == header[1][0]:
        ax1.plot(data[0], data[i], label = header[i], linestyle="-")
    else:
        ax2.plot(data[0], data[i], label = header[i], linestyle="-", color=next(ax1._get_lines.prop_cycler)['color'])
        secondAxis = True



ylabel = get_axis_label(header[1])


if secondAxis:
    ylabel2 = ""
    for i in range(2, len(header)):
        if header[i][0] != header[1][0]:
            ylabel2 = get_axis_label(header[i])
    ax2.set_ylabel(ylabel2, fontsize=12)

ax1.set_ylabel(ylabel, fontsize=12)

lines_labels = [ax.get_legend_handles_labels() for ax in fig.axes]
lines, labels = [sum(lol, []) for lol in zip(*lines_labels)]
plt.legend(lines, labels, loc="best")

plt.show()