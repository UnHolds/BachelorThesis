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

![[Sinus_44100Hz_100Hz_1V5_2V5_Amplitude.JPG]]
![[I2C_Lautsprecher_System/Experiments/pictures/oszi/DAC_Signal/Sinus_44100Hz_100Hz_1V5_2V5_Frequency.JPG]]
![[Sinus_44100Hz_100Hz_1V5_2V5_Offset.JPG]]

| Parameter | Wert |
|----|------|
| Form | DAC-Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 1000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |


![[Sinus_44100Hz_1kHz_1V5_2V5_Amplitude.JPG]]
![[I2C_Lautsprecher_System/Experiments/pictures/oszi/DAC_Signal/Sinus_44100Hz_1kHz_1V5_2V5_Frequency.JPG]]
![[Sinus_44100Hz_1kHz_1V5_2V5_Offset.JPG]]



| Parameter | Wert |
|----|------|
| Form | DAC-Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 10000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

![[Sinus_44100Hz_10kHz_1V5_2V5_Amplitude.JPG]]
![[I2C_Lautsprecher_System/Experiments/pictures/oszi/DAC_Signal/Sinus_44100Hz_10kHz_1V5_2V5_Frequency.JPG]]
![[Sinus_44100Hz_10kHz_1V5_2V5_Offset.JPG]]

### Triangle

| Parameter | Wert |
|----|------|
| Form | DAC-Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 100 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |


![[Triangle_44100Hz_100Hz_1V5_2V5_Amplitude.JPG]]
![[I2C_Lautsprecher_System/Experiments/pictures/oszi/DAC_Signal/Triangle_44100Hz_100Hz_1V5_2V5_Frequency.JPG]]
![[Triangle_44100Hz_100Hz_1V5_2V5_Offset.JPG]]

| Parameter | Wert |
|----|------|
| Form | DAC-Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 1000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |


![[Triangle_44100Hz_1kHz_1V5_2V5_Amplitude.JPG]]
![[I2C_Lautsprecher_System/Experiments/pictures/oszi/DAC_Signal/Triangle_44100Hz_1kHz_1V5_2V5_Frequency.JPG]]
![[Triangle_44100Hz_1kHz_1V5_2V5_Offset.JPG]]


| Parameter | Wert |
|----|------|
| Form | DAC-Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 10000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |


![[Triangle_44100Hz_10kHz_1V5_2V5_Amplitude.JPG]]
![[I2C_Lautsprecher_System/Experiments/pictures/oszi/DAC_Signal/Triangle_44100Hz_10kHz_1V5_2V5_Frequency.JPG]]
![[Triangle_44100Hz_10kHz_1V5_2V5_Offset.JPG]]

### Rechteck Abtastfrequenz
Dies Simulation gibt ein Rechtecksignal mit der halben Abtastgeschwindigkeit aus 

![[Rectangle_44100Hz_22k05Hz_1V5_2V5_Frequency.JPG]]

![[Rectangle_44100Hz_22k05Hz_1V5_2V5_Frequency_Half.JPG]]


### Sinus-Abtastfrequenz

| Parameter | Wert |
|----|------|
| Form | DAC-Triangle |
| Abtastrate | 44100 Hz |
| Frequenz | 1000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |

![[Abtastfrequenz_Measurement_Zoom.JPG]]


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

![[Sinus_44100Hz_100Hz_1V5_2V5_Amplitude.JPG]]
![[I2C_Lautsprecher_System/Experiments/pictures/oszi/DAC_Signal/Sinus_44100Hz_100Hz_1V5_2V5_Frequency.JPG]]
![[Sinus_44100Hz_100Hz_1V5_2V5_Zoom.JPG]]



| Parameter | Wert |
|----|------|
| Form | DAC-Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 1000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |



![[Sinus_44100Hz_1kHz_1V5_2V5_Amplitude.JPG]]
![[I2C_Lautsprecher_System/Experiments/pictures/oszi/DAC_Signal/Sinus_44100Hz_1kHz_1V5_2V5_Frequency.JPG]]
![[Sinus_44100Hz_1kHz_1V5_2V5_Zoom.JPG]]
![[Sinus_44100Hz_1kHz_1V5_2V5_ZoomZoom.JPG]]


| Parameter | Wert |
|----|------|
| Form | DAC-Sinus |
| Abtastrate | 44100 Hz |
| Frequenz | 10000 Hz |
| Amplitude | 1.5V |
| Offset | 2.5V |


![[Sinus_44100Hz_10kHz_1V5_2V5_Amplitude.JPG]]
![[I2C_Lautsprecher_System/Experiments/pictures/oszi/DAC_Signal/Sinus_44100Hz_10kHz_1V5_2V5_Frequency.JPG]]
![[Sinus_44100Hz_10kHz_1V5_2V5_Zoom.JPG]]
![[Sinus_44100Hz_10kHz_1V5_2V5_ZoomZoom.JPG]]


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

![[Triangle_44100Hz_100Hz_2V048_2V048_MaxValue.JPG]]

| Parameter | Wert |
|----|------|
| Form | Sinus |
| Frequenz | 1000 Hz |
| Amplitude | 2.5V |
| Offset | 2.5V |

![[Sinus_1kHz_2V5_2V5_MaxValuesFilter_Amplitude.JPG]]
![[Sinus_1kHz_2V5_2V5_MaxValuesFilter_ClipVoltage.JPG]]

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

![[Sinus_19k4_1V5_2V5_AmplitudeInput.JPG]]
![[Sinus_19k4_1V5_2V5_AmplitudeOutput.JPG]]
![[Sinus_19k4_1V5_2V5_Frequency.JPG]]
![[Sinus_19k4_1V5_2V5_PhaseShift.JPG]]