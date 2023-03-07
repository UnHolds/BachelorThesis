## Idee

Es wird ein OPV verwendet, um eine zweite Versorgungsspannung VCC2 zu erzeugen. Diese Spannung ist etwas kleiner als die eigentliche VCC Spannung. Des Weiteren soll die VCC2  dynamisch eingestellt werden können (via Trimmer).
Diese Spannungen werden dann verwenden, um zwei 74HC00 Quad-Nand-Gatter mit verschiedenen Spannungen zu versorgen. Dies führt dann dazu, dass sich die Logikschwelle verschiebt und somit mit einer Eingangspannung zwei verschiedene Ausgangszustände erzeugt werden. 

## Berechnungen

### Zweite Spannungsversorgung

![[Schemati_PowerSupply.svg#invert_W]]

RP1 ist ein Timmer mit 10k.

VCC = 5V
Minimale Spannung = $\frac{VCC}{RP1 + R3} * R3= \frac{5V}{10k + 10k} * 10k = \frac{VCC}{2} = 2.5V$ 
Maximale Spannung = 5V


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

[[Metastabile_NAND-Gatter/Simulation/Simulation|Simulation]]

## Experimente

[[Metastabile_NAND-Gatter/Experiments/Experimente|Experimente]]

