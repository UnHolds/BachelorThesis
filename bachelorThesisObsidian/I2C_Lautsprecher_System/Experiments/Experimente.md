## Signaltest DAC
### Beschreibung
In diesem Experiment werden verschiedene Signalformen und Frequenzen 
mit dem DAC [[MCP4801]] erzeugt und gemessen.

### Sinus

| Parameter | Wert |
|----|------|
| Form | DAC-Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 100 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_28_45 2023-08-25
Timestamp: 17_28_50 2023-08-25
Timestamp: 18_10_00 2023-08-25

| Parameter | Wert |
|----|------|
| Form | DAC-Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 1000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_31_30 2023-08-25
Timestamp: 17_32_00 2023-08-25
Timestamp: 18_09_15 2023-08-25

| Parameter | Wert |
|----|------|
| Form | DAC-Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 10000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_36_00 2023-08-25
Timestamp: 17_37_00 2023-08-25
Timestamp: 18_08_10 2023-08-25

### Triangle

| Parameter | Wert |
|----|------|
| Form | DAC-Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 100 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_43_00 2023-08-25
Timestamp: 17_43_30 2023-08-25
Timestemp: 18_05_00 2023-08-25

| Parameter | Wert |
|----|------|
| Form | DAC-Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 1000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_44_45 2023-08-25
Timestamp: 17_45_05 2023-08-25
Timestamp: 18_05_55 2023-08-25


| Parameter | Wert |
|----|------|
| Form | DAC-Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 10000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_46_30 2023-08-25
Timestamp: 17_47_00 2023-08-25
Timestamp: 18_07_10 2023-08-25

### Rechteck Abtastfrequenz
Dies Simulation gibt ein Rechtecksignal mit der halben Abtastgeschwindigkeit aus 

Timestamp: 17_50_15 2023-08-25
Timestamp: 17_50_35 2023-08-25

### Sinus-Abtastfrequenz

| Parameter | Wert |
|----|------|
| Form | DAC-Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 1000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_52_30 2023-08-25

## Signaltest Filter

## Normalbetrieb

### Beschreibung
In diesem Experiment wird der Normalbetrieb getestet und verglichen, ob das Ausgangssignal der [[I2C_Lautsprecher_System/Simulation/Simulation#Transient Simulation Normalbetrieb|Simulation]] entspricht. 

### Ergebnis


| Parameter | Wert |
|----|------|
| Form | DAC-Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 100 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_39_20
Timestamp: 17_39_55
Timestamp: 17_55_15


| Parameter | Wert |
|----|------|
| Form | DAC-Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 1000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_41_10
Timestamp: 17_41_25
Timestamp: 17_46_30
Timestamp: 17_47_00

| Parameter | Wert |
|----|------|
| Form | DAC-Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 10000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_42_55
Timestamp: 17_43_30
Timestamp: 17_44_50
Timestamp: 17_45_10#

| Parameter | Wert |
|----|------|
| Form | DAC-Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 10000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 17_42_55
Timestamp: 17_43_30
Timestamp: 17_44_50
Timestamp: 17_45_10



| Parameter | Wert |
|----|------|
| Form | Sinus |
| Frequenz | 1000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 18_13_10
Timestamp: 18_14_20



## Maximale Werte

### Beschreibung 
In dieser Simulation werden die maximalen Eingangspegel für den Verstärker ermittelt.
Vergleiche: [[I2C_Lautsprecher_System/Simulation/Simulation#Transient Simulation Übersteuern|Simulation]]

### Ergebnis DAC

| Parameter | Wert |
|----|------|
| Form | DAC-Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 100 Hz |
| Amplitude | 2.048V |
| Offset | 2.048V |

Timestamp: 17_59_20  2023-08-25

| Parameter | Wert |
|----|------|
| Form | Sinus |
| Frequenz | 1000 Hz |
| Amplitude | 2.5V |
| Offset | 2.5V |

Timestamp: 18_21_30
Timestamp: 18_21_50
## Filter-Test

### Beschreibung
In diesem Experiment wird der Filter getestet, ob er die gewünschte Grenzfrequenz hat und wie das  Signal vor und nach dem Filter aussieht. Vergleiche: [[I2C_Lautsprecher_System/Simulation/Simulation#Transient Simulation Tiefpass-Filter |Simulation Filter 1]], [[I2C_Lautsprecher_System/Simulation/Simulation#Transient Simulation 19.4kHz|Simulation Filter 2]], [[I2C_Lautsprecher_System/Simulation/Simulation#FFT Simulation 19.4kHz|Simulation Filter 3]]

### Ergebnis 


| Parameter | Wert |
|----|------|
| Form | Sinus |
| Frequenz | 19400 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

Timestamp: 18_09_15
Timestamp: 18_10_20
Timestamp: 18_10_45
Timestamp: 18_11_40