
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