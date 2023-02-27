
## Aufbau

![[Schematic_74HC00_DAC.svg|1000]]


![[Schemati_PowerSupply.svg|300]]


## Parameter

| Parameter | Wert |
|-----------|------|
| VCC | 5V |
| VCC2 |4.75V |
| DAC States | 256 (8Bit) |
| Pulse | Sägezahn 0-5V 10Hz |


## Transient Simulation

Time: 250ms

![[TransientPlot.svg]]

Hier können wir sehen, dass die zwei NAND-Gatter zu verschiedenen Zeitpunkten schalten. Somit existiert eine Spannung, wo eines des Gatter HIGH ausgibt und das andere LOW.


## Transient Simulation Metastabiler Punkt

In dieser Simulation wird der metastabile Zeitraum genauer untersucht, um herauszufinden, wie groß der metastabile Spannungsraum ist.

![[TransientPlotMetastablePoint.svg]]


| | Time | Voltage |
| -|---|--|
| V-LOW | 7.47mS | 2.383V |
| V-HIGH | 10.19mS | 2.5V |

Metastabiler Spannungsbereich bei VCC=2.5V und VCC2=4.75V ist 0.117V