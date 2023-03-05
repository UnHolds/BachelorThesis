
## Schaltunterschied

### Beschreibung
In diesem Experiment geht es darum, eine Umschaltverzögerung zu erkennen. Vergleiche [[Metastabile_NAND-Gatter/Simulation/Simulation#Transient Simulation|Simulation 1]] [[Metastabile_NAND-Gatter/Simulation/Simulation#Transient Simulation Metastabiler Punkt|Simulation 2]]
Jedoch wird das hier nicht nur für eine spezielle Versorgungsspannung überprüft, sondern für eine ganze Reihe an Versorgungsspannungen. Um die verschiedenen Versorgungsspannungen zu erzeugen, wird ein DAC verwendet. Des Weiteren soll der ganze Messablauf automatisiert ablaufen.

### Aufbau
![[Aufbau.svg|500]]

### Ablauf

Der DAC für die Versorgungsspannung einer der NAND-Gatter auf 5V eingestellt, das andere NAND-Gatter wird auch mit 5V versorgt jedoch nicht über den DAC. Danach wird mit dem DAC der am In-Port des DUT (Device under Test) hängt, eine Rampe ausgegeben 0V -> 5V. Währenddessen werden beide Ausgänge (Out1 & Out2) über die beiden ADC mitgemessen, wenn der DAC der am In-Pin hängt, 5V erreicht hat, ist der erste Testlauf fertig. Nun wird die Spannung vom DAC für VCC verringert und ein neuer Testlauf startet. Die Spannung des VCC DACs wird so lange verringert, bis sie den minimalen Wert laut Datenblatt erreicht hat. 

#### Kurzfassung:

* Step 1: VCC für NAND-Gatter1 auf 5V setzen (statisch)
* Step 2: VCC für NAND-Gatter2 auf 5V setzen via DAC
* Step 3: Step Spannung auf In-Pin vom 0V zu 5V (Rampe)
* Step 4: Spannung an Out1, Out2, VCC (DAC) messen während Step 3
* Step 5: VCC Spannung (via DAC) verringern und bei Step 3 weitermachen, bis die minimale Versorgungsspannung des NAND-Gatters laut Datenblatt erreicht wurde.
* Step 6: Done


### Ergebnis

#TODO