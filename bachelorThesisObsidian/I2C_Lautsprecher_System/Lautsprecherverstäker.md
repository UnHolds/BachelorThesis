
## Idee

![[Functional_Blocks_AMP.svg#invert_W]]

Der DAC erzeugt das Audiosignal welchen das durch einen Tiefpassfilter geht, der die hochfrequenten Anteile des Signales entfernt. Danach geht das Signal durch einen Treiber der verwendet wird um den Lautsprecher zu treiben.

## Berechnungen

Transistor: [[2N3055]]
* Ic = 4000mA
* Gain = 20 - 70
* Vbe = 1.5V

Lautsprecher
* Ri = 8$\ohm$
* Pmax = 3W 

OPV: [[LM4562]]
* Leider gibt es in LT-Spice den OPV nicht, daher wurde ersatzhalberder OPV LT1677 verwendet.

DAC: [[MCP4801]]
* Für diesen DAC wurde ein eigenes ideals Model für die Simulation erzeugt. Siehe [[Lautsprecherverstäker#LT-Spice Model DAC|LT-Spice Model DAC]] 

### Verstärker Schematic:
![[Speaker_Amp_Schematic.svg#invert_W]]


### Rechnung:

#### Lautsprecher
Maximum Strom durch Lautsprecher
$I_{s_{max}} = \frac{3W}{5V} = 600mA$

Maximale theoretische Spannung am Lautsprecher
$U_{s_{max}} = R_i * I_{s_{max}} = 8\ohm * 600mA = 4.8V$


#### Low-Pass Filter
Max Frequenz = 20khz 

$f_g = \frac{1}{2\pi RC}$
$C = \frac{1}{2\pi R f_g} = \frac{1}{2 \pi * 820\ohm * 20kHz} = 9.7nF \approx 10nF$

Backtracking
$f_g = \frac{1}{2\pi RC} = \frac{1}{2 \pi * 820\ohm * 10nF} = 19.4kHz$

R = $820\ohm$
F = $10nF$

### LT-Spice Model DAC

Den DAC gibt es leider auch nicht im LT-Spice daher wurde ein perfekter DAC moderiert des die Eingangspannung am PIN 1 auf die definierten Anzahl "States" abbildet. Dabei wird die definierte Spannung VCC (Variable) verwendet.

#### Model Code

```
* MCP4801

.subckt MCP4801 In Out

Ri In 0 {Ri}
E1 Out 0 value={round(V(In,0)/(Vcc / States)) * Vcc / States}

.ends MCP4801
```


## Simulation

[[I2C_Lautsprecher_System/Simulation/Simulation|Simulation]]


## Experimente

[[I2C_Lautsprecher_System/Experiments/Experimente|Experimente]]

## Prototypen

[[Speaker Prototyp 1.0]]
[[Speaker Prototyp 1.0]]
[[Audio Controller Prototyp 1.0]]

## MOSI Widerstand

![[res_1k_series_freq_amp.png]]
Widerstand 1k = scope_0 scope_1 scope_2


![[res_2_5_series_freq_amp.png]]
Widerstand auf Audio Controller: $4 * 10\ohm\ (parallel)= 2.5\ohm$ 

![[res_3x10_series_freq_amp.png]]
scope_4  = 3 * 10ohm para

![[res_2x10_series_freq_amp.png]]
scope_5 = 2 * 10 ohm para

![[res_10_series_freq_anm.png]]
scope_6 = 10 ohm


![[res_100_series_freq_amp.png]]
![[res_100_series_freq_amp_speaker.png]]
scope_7 = 100ohm  (scope_8 = with 5 speaker)

![[res_2x100_series_freq_amp.png]]
![[res_2x100_series_freq_amp_speaker.png]]
scope_9 2x 100 ohm  (scope_10 = with 5 speakers)

![[res_3x100_series_freq_amp.png]]
![[res_3x100_series_freq_amp_speaker.png]]
scope_11 3* 100ohm (scope_12 = with 5 speakers)



![[res_3x100_load_128_dead.png]]
dead at 126 ohm scope_13
min work = 512ohm
220 dead
330 störung



![[res_3x100_2k_per_speaker_4_speaker_amp.png]]
![[res_3x100_2k_per_speaker_4_speaker_freq.png]]
jede box 2k 
messung 4 angeschlossen: scope_14 scope_15


![[res_3x100_2k_per_speaker_5_speaker_freq.png]]
![[res_3x100_2k_per_speaker_5_speaker_amp.png]]
messung 5 angeschlossen: scope_16 scope_17