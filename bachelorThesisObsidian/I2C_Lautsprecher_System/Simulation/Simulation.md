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

In diesem Fall sollte die Endstufe nicht mehr nachkommen und das Signal übersteuerten. 

