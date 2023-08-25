## Signaltest DAC
### Beschreibung
In diesem Experiment werden verschiedene Signalformen und Frequenzen 
mit dem DAC [[MCP4801]] erzeugt und gemessen.

### Sinus

| Parameter | Wert |
|----|------|
| Form | Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 100 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_28_45
Timestamp: 17_28_50
Timestamp: 18_10_00

| Parameter | Wert |
|----|------|
| Form | Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 1000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_31_30
Timestamp: 17_32_00
Timestamp: 18_09_15

| Parameter | Wert |
|----|------|
| Form | Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 10000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_36_00
Timestamp: 17_37_00
Timestamp: 18_08_10

### Triangle

| Parameter | Wert |
|----|------|
| Form | Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 100 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_43_00
Timestamp: 17_43_30
Timestemp: 18_05_00

| Parameter | Wert |
|----|------|
| Form | Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 1000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_44_45
Timestamp: 17_45_05
Timestamp: 18_05_55


| Parameter | Wert |
|----|------|
| Form | Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 10000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_46_30
Timestamp: 17_47_00
Timestamp: 18_07_10

### Rechteck Abtastfrequenz
Dies Simulation gibt ein Rechtecksignal mit der halben Abtastgeschwindigkeit aus 

Timestamp: 17_50_15
Timestamp: 17_50_35

### Sinus-Abtastfrequenz

| Parameter | Wert |
|----|------|
| Form | Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 1000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_52_30

## Signaltest Filter

## Normalbetrieb

### Beschreibung
In diesem Experiment wird der Normalbetrieb getestet und verglichen, ob das Ausgangssignal der [[I2C_Lautsprecher_System/Simulation/Simulation#Transient Simulation Normalbetrieb|Simulation]] entspricht. 

### Parameter

| Parameter | Wert |
|----|------|
| Eingangssignal | Sinus 1kHz , 4V Vpp, 2.5V Offset |

### Ergebnis

#TODO


## Maximale Werte

### Beschreibung 
In dieser Simulation werden die maximalen Eingangspegel für den Verstärker ermittelt.
Vergleiche: [[I2C_Lautsprecher_System/Simulation/Simulation#Transient Simulation Übersteuern|Simulation]]

### Ergebnis DAC

| Parameter | Wert |
|----|------|
| Form | Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 100 Hz |
| Amplitude | 2.048V |
| Offset | 2.048V |

Timestamp: 17_59_20


#TODO



## Filter-Test

### Beschreibung
In diesem Experiment wird der Filter getestet, ob er die gewünschte Grenzfrequenz hat und wie das  Signal vor und nach dem Filter aussieht. Vergleiche: [[I2C_Lautsprecher_System/Simulation/Simulation#Transient Simulation Tiefpass-Filter |Simulation Filter 1]], [[I2C_Lautsprecher_System/Simulation/Simulation#Transient Simulation 19.4kHz|Simulation Filter 2]], [[I2C_Lautsprecher_System/Simulation/Simulation#FFT Simulation 19.4kHz|Simulation Filter 3]]

### Ergebnis 

#TODO 
