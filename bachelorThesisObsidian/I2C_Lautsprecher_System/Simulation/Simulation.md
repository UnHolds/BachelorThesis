## Aufbau
![[Speaker_Amp_Schematic.svg]]


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


## Transient Simulation Tiefpass-Filter

### Simulation 1kHz

In dieser Simulation wird der Tiefpass-Filter untersucht und welche Auswirkungen er auf das DAC Signal hat.
![[I2C_Lautsprecher_System/Simulation/Simulation#Parameter]]

Simulations-Zeit: 1ms

![[LowPassFilterTransientSimulation.svg]]

Vergrößerte Version:
![[LowPassFilterTransientSimulationZoomed.svg]]

Es ist zu erkennen, dass das Signal nach dem Filter wesentlich weniger "Störungen" beinhaltet als nach dem DAC.

### Transient Simulation 19.4kHz

19.4kHz ist die errechnete Grenzfrequenz des Tiefpasses. Hier sollte das Signal 3dB (30%) kleiner sein als das Eingangsignal.

![[LowPassFilterTransientSimulation19_4kHz.svg]]

| Parameter | Wert |
| --|-|
| Vpp DAC | 3.986V |
| Vpp after Filter| 2.929V |

Erwartungswert: $3.986V -3dB = 3.986V * \frac{1}{\sqrt{2}}=2,8185V$

Der Filter passt nicht genau, jedoch ist diese Abweichung nicht so tragisch in der Simulation. Die wahre Abweichung wird dann ohnehin im Prototypen gemessen und anhand dessen wird festgestellt, ob die Abweichung kritisch ist oder weniger kritisch. Eine weitere Überlegung wäre es, den Filter für eine höhere Grenzfrequenz zu konzipieren, sodass die Signale bis 20kHz sauberer Übertragen werden.

### FFT Simulation 19.4kHz

![[LowPassFilterFFT19_4kHz.svg]]

Vergrößerte Ansicht: [[LowPassFilterFFT19_4kHz.svg]]

Pink: Nach dem Filter
Grün: DAC Signal

In dieser FFT-Ansicht ist gut zu erkennen, dass der Filter ein wesentlich störungsfreieres Signal liefert als der DAC. Der Grund hierfür ist das Filtern der Oberwellen, die durch den DAC entstehen. Der Prototyp wird höchstwahrscheinlich keine so großen Oberwellen erzeugen wie in dieser Simulation, da der [[MCP4801]] eine endliche Slew-Rate (0.55$\frac{V}{\mu s}$) besitzt. Somit wäre die maximale Frequenz bei 4V:

$\frac{5V}{0.55\frac{V}{\mu s}} = 9.091\mu s \rightarrow \frac{1}{9.091\mu s} = 110kHz$  

Die Ausgangsspannung des [[MCP4801]] kann laut [[MCP4801.pdf|Datenblatt]] mit folgender Formel errechnet werden:

$V_{OUT} = \frac{2.048V * D_n}{2^8} * G$

Wir setzen bei uns den Gain auf 2, um die maximale Wertebreite auszureizen. Dh die minimal erzielbare Vpp ist:

$V_{Vpp_{min}} = \frac{2.048V * (D_n + 1)}{2^8} * 2 - \frac{2.048V * D_n}{2^8} * 2 = 0.016V = 16mV$

Mit dieser $Vpp_{min}$ kann nun die maximal erzeugbare Frequenz ausgerechnet werden:

$F_{max} = \frac{1}{\frac{0.016V}{0.55\frac{V}{\mu s}}} = 34.375Mhz$ 

Somit können theoretische alle Werte nach 34.375Mhz in der FFT ignoriert werden. Des Weiteren würden auch die dB darauf schließen lassen, dass der Filter möglicherweise nicht benötigt wird.