## Aufbau

![[Speaker_Amp_Schematic2.svg]]


## Parameter

| Parameter | Wert |
| ----------|------|
| VCC / 5V | 5V |
| DAC | 256 (8Bit) |
| Signal | Sinus 1kH, 4V Vpp, 2.5V Offset |

## Transient Simulation Normalbetrieb

Zeit: 3ms

![[BasicTransientInputOutputCurrent.svg]]

In dieser Simulation ist zu erkennen, dass das Signal sauber vom Eingang an den Ausgang weitergegeben wird. Auch der Strom durch den Lautsprecher befindet sich im erwartetem Rahmen.
In dieser Simulation wurden die Erwartungswerte simuliert und ein "Proof-Of-Concept"

| Parameter | Wert |
| ----------|------|
| V_out MAX | 4.038V |
| V_out MIN | 0.156V |
| I Speaker MAX | 505mA |
| I Speaker MIN | 19.5mA |


## Transient Simulation Übersteuern

Für diese Simulation werden die Werte der Signalquelle erhört auf folgende Werte:

| Parameter | Wert |
| -|-|
| Signal | 1kHz, 5V Vpp, 2.5V Offset |
| VCC OPV | 8V |

In diesem Fall sollte die Endstufe nicht mehr nachkommen und das Signal übersteuerten. 

![[OverdriveTransientInputOutputCurrent.svg]]

In dieser Simulation sieht man nun die Grenzen der Schaltung.

| Parameter | Wert |
| ----------|------|
| V_out MAX | 4.539V |
| V_out MIN | ~0V |
| I Speaker MAX | 567mA |
| I Speaker MIN | ~0mA |


Dieses neu erlangte Wissen wird jetzt verwendet, um die maximale und minimale Spannung herauszufinden, die der Endstufe übergeben werden darf, ohne dass diese übersteuert.
Um das Finden etwas einfacher zu gestalten, wird das Input-Signal auf ein Dreieckssignal angepasst.

![[TriangleFindMinMaxVoltageTransientInputOutput.svg]]

Minimale Eingangsspannung: ca. __300mV__ 

Die maximale Eingangsspannung wird vom OPV vorgegeben [[LM4562]], dieser folgt folgendem Diagramm:

![[LM4562_Supply_Output_Voltage.svg|400]]

Dies führt zu zwei Möglichkeiten:
1. Es wird eine Versorgungsspannung für den OPV von > 7.5V gewählt
2. Die maximale Input-Spannung ist ca. 3.8V

Welche von den beiden Varianten verwendet wird, wird nach dem Bau des Prototyps entschieden. 
Info: In der Simulation wird der OPV TL1677 verwendet und nicht der OPV [[LM4562]], der Grund hierfür ist das LTSpice diesen nicht in der Bibliothek hat, der einzige Unterschied sollte jedoch nur sein, dass der TL1677 näher an die Versorgungsspannung kommt als der [[LM4562]]

