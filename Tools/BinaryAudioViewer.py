import matplotlib.pyplot as plt

sample_rate = 22050 #Hz


data = None
with open("CantinaBand60.bwav", "rb") as f:
    data = f.read()

print(len(data))

plt.plot(range(0, len(data)), list(data))
plt.show()