
## Schaltunterschied

### Beschreibung
In diesem Experiment geht es darum, eine Umschaltverzögerung zu erkennen. Vergleiche [[Metastabile_NAND-Gatter/Simulation/Simulation#Transient Simulation|Simulation 1]] [[Metastabile_NAND-Gatter/Simulation/Simulation#Transient Simulation Metastabiler Punkt|Simulation 2]]
Jedoch wird das hier nicht nur für eine spezielle Versorgungsspannung überprüft, sondern für eine ganze Reihe an Versorgungsspannungen. Um die verschiedenen Versorgungsspannungen zu erzeugen, wird ein DAC verwendet. Des Weiteren soll der ganze Messablauf automatisiert ablaufen.

### Aufbau
![[Aufbau.svg|500]]



![[DUT.png|400]]
### Ablauf

Der DAC für die Versorgungsspannung einer der NAND-Gatter auf 5V eingestellt, das andere NAND-Gatter wird auch mit 5V versorgt, jedoch nicht über den DAC. Danach wird mit dem DAC der am In-Port des DUT (Device under Test) hängt, eine Rampe ausgegeben 0V -> 5V. Währenddessen werden beide Ausgänge (Out1 & Out2) über die beiden ADC mitgemessen, wenn der DAC der am In-Pin hängt, 5V erreicht hat, ist der erste Testlauf fertig. Nun wird die Spannung vom DAC für VCC verringert und ein neuer Testlauf startet. Die Spannung des VCC DACs wird so lange verringert, bis sie den minimalen Wert laut Datenblatt erreicht hat. 

#### Kurzfassung:

* Step 1: VCC für NAND-Gatter1 auf 3.3V setzen (statisch)
* Step 2: VCC für NAND-Gatter2 auf 4.096V setzen via DAC
* Step 3: Step Spannung auf In-Pin vom 0V zu 5V (Rampe)
* Step 4: Spannung an Out1, Out2, VCC (DAC) messen während Step 3
* Step 5: VCC Spannung (via DAC) verringern und bei Step 3 weitermachen, bis die minimale Versorgungsspannung des NAND-Gatters laut Datenblatt erreicht wurde.
* Step 6: Done


### Ergebnis

Hier einige Auszüge aus den Ergebnissen. (Komplette Ergebnisse in "nand_experiment_3_3V_C.csv")

#### VCC: 255 (4.096V)
![[NAND_Experiment_VCC_255.png]]


#### VCC: 220 (3.52V)
![[NAND_Experiment_VCC_220.png]]


#### VCC: 213 (3.408V)
![[NAND_Experiment_VCC_213.png]]


#### VCC: 207 (3.312V)
![[NAND_Experiment_VCC_207.png]]

#### VCC: 200 (3.2V)
![[NAND_Experiment_VCC_200.png]]

#### VCC: 189 (3.024V)
![[NAND_Experiment_VCC_189.png]]


### Steckbrett Aufbau

![[Aufbau_Steckbrett.jpg]]


## Messung Metastabilität invertiertes RS-FF

### Schaltung

![[schaltung_inverted_rs.png|400]]

### Wahrheitstabelle

Input 1 | Input 2 | Output 1 | Output 2
--------|---------|----------|-----
L       | L       | H        | H
L       | H       | H        | L
H       | L       | L        | H
H       | H       | X1       | X2

Für Zustand Input 1 == H und Input 2 == H:

Wenn vorher Input1 = H und Input2 = L, dann X1 = L und X2 = H.
Wenn vorher Input2 = L und Input2 = H, dann X1 = H und X2 = L.
Wenn vorher Input2 = H und Input2 = H, dann vorheriger Zustand für  X1 und X2.
Wenn vorher Input2 = L und Input2 = L, dann metastabiler Zustand.

### Experiment 1

In diesem Experiment werden die beiden Inputs (Input 1 und Input 2) zusammen verbunden und über einen DAC kontrolliert. Des Weiteren wird die Spannungsversorgung des 74HC00 Gatters auch über einen DAC kontrolliert. Das Experiment startet mit der minimal gesetzten Versorgungsspannung.
Während des Experimentablaufes wird die Spannung am Input immer weiter erhöht, bis das Maximum erreicht wurde. Danach wird die Spannung am Input wieder auf das Minimum gesetzt und die Versorgungsspannung erhöht. Dies geht so lange, bis die maximale Versorgungsspannung erreicht wurde. 
Gemessen werden folgende Werte:
* VCC
* Input
* Output 1
* Output 2


Dieses Experiment wurde zweimal durchgeführt. Beim ersten Mal, ohne dass LEDs angeschlossen waren und beim zweiten Mal mit angeschlossenen LEDs.

#### Ablauf

* Step 1: VCC auf das Minimum setzen (DAC 128)
* Step 2: Input auf das Minimum setzen (DAC 0)
* Step 3: Input um 1 erhöhen
* Step 4: Messen (VCC, Input, Output 1, Output 2)
* Step 5: Bei step 3 weitermachen, bis die maximale Input-Spannung erreicht wurde.
* Step 6: VCC Spannung erhöhen
* Step 7: Bei step 2 weitermachen bis die maximale VCC Spannung erreicht wurde
* Step 8: DONE


#### Ergebnis 

Hier einige Auszüge, für alle Daten die "csv" files beachten.


#TODO hier bilder einfügen

#### Steckbrett Aufbau

#TODO insert image


### Experiment 2

In diesem Experiment werden die Inputs einzeln beschalten via DACs. Die Versorgungsspannung wird auf 5V gesetzt. Während des Experiments wird zuerst die Spannung am Input 1 erhöht, bis sie die maximale Spannung erreicht hat. Danach wird die Spannung am Input 1 wieder auf 0 gesetzt und die Spannung am Input 2 um 1 erhöht. Das Experiment ist fertig, wenn Input 2 die maximale Spannung erreicht hat. Nach jedem Wert wechsel des DACs werden folgende Spannungen gemessen: 
* Input 1
* Input 2
* Output 1
* Output 2

#### Ablauf 
* Step 1: DAC von Input 2 auf 0 setzen.
* Step 2: DAC von Input 1 auf 0 setzen.
* Step 3: DAC von Input 1 um 1 erhöhen
* Step 4: Bis die maximale Spannung am Input 1 erreicht wird, mit step 3 weitermachen.
* Step 5: DAC von Input 2 um 1 erhören
* Step 6: Bis die maximale Spannung am Input 2 erreicht wird, mit step 2 weitermachen.
* Step 7: DONE

#### Ergebnis

#TODO bilder hier einfügen 

#### Steckbrett Aufbau

Gleich wie bei [[Metastabile_NAND-Gatter/Experiments/Experimente#Experiment 1|Experiment 1]]


### Experiment 3

Dieses Experiment ist eine Weiterführung des [[Metastabile_NAND-Gatter/Experiments/Experimente#Experiment 1|Experimente 1]]. Grund dafür ist, dass ein mögliches Schwingen in dem metastabilen Zustand vermutet wird, welches aufgrund der hohen Frequenz nicht von der automatischen Messung erfasst wurde. Daher wird in diesem Experiment nicht automatisch gemessen, sondern mithilfe eines Oszilloskops. Im Aufbau selbst hängen die Signale an folgenden Channels:
* Input = Channel 1
* Output 1 = Channel 2
* Output 2 = Channel 3

Die Spannung des Inputs wird wieder mithilfe eines DACs kontrolliert. Für diesen speziellen Zweck wurde Code entwickelt, der es ermöglicht, die DAC Spannung mithilfe von seriellen Befehlen zu setzen. 

`CMD: A<value>` - Setzt den DAC auf den Wert \<value\> eg. 128

Für alle Messungen wurde der DAC auf den Wert 168 gesetzt, denn dort befindet sich das invertierte RS-FF in einem metastabilen Zustand. 

#### Messung Signale Single-Run

##### Input Signal
![[scope_0_measure_input_signal.png]]

![[scope_3_input_measure_multidata.png]]



##### Output 1 Signal
![[scope_1_measure_output_1.png]]

![[scope_4_output__measure_multidata.png]]



##### Output 2 Signal 
![[scope_2_measure_output_2.png]]

![[scope_5_output_2_measure_multidata.png]]

Hier ist die Frequenzmessung beim 2. Bild falsch. Sollte im Bereich von 78Mhz liegen. 


#### Messung Running

![[scope_6_signal_running_unstable.png]]

Hier sieht man das Signal alles Pins. Dieses Signal ist sehr instabil, bereits ein Nähern mit der Hand verändert die Frequenz und/oder die Amplitude.


![[scope_7_signal_running_100nF_input.png]]

Hier wurde ein 100nF Kondensator an den Eingangspin gehängt. Das Signal hat nun eine kleinere Amplitude, jedoch immer noch sehr instabil.


![[scope_8_measure_RMS_100nF_input.png]]

Hier hängt immer noch ein 100nF Kondensator am Input. Die RMS Werte sind:

Signal | Wert
-|-
Input | 2.512V
Output 1 | 4.618V
Output 2 | 2.709V

Hier ist zu erkennen, dass das Signal des Output 2 eher low ist. Dies kann verändert werden, indem man einen Kondensator kurz an die Pins hängt.
In den folgenden Bildern sind beide Fälle abgebildet (Output 1 "low" / Output 2 "low")


Output 1 Low
![[scope_9_measure_RMS_ouput_1_low.png]]


Output 2 Low
![[scope_10_measure_output_2_low.png]]

#### Steckbrett Aufbau

#TODO insert image 

### Erkenntnisse

Die Vermutungen, dass die Schaltung schwingt, haben sich als wahr erwiesen. Somit ist dieser metastabile Zustand nicht verwendbar für die angedachte Schaltung.