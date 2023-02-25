import matplotlib.pyplot as plt
import sys
from tkinter.filedialog import askopenfilename


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

    


# plot lines
for i in range(1, len(header)):
    plt.plot(data[0], data[i], label = header[i], linestyle="-")

plt.xlabel('Time [s]', fontsize=12)

ylabel = ""
if header[1][0] == "V":
    ylabel = "Voltage [V]"
elif header[1][0] == "I":
    ylabel = "Current [A]"


plt.ylabel(ylabel, fontsize=12)
plt.legend()
plt.show()