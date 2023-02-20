
## Brechnungen

Transistor: [[2N3055]]
* Ic = 4000mA
* Gain = 20 - 70
* Vbe = 1.5V

Lautsprecher
* Ri = 8ohm
* Pmax = 3W 

Emitter Verstärker Schematic:


### Rechnung:

Maximum Strom durch Lautsprecher
$I_{s_{max}} = \frac{3W}{5V} = 600mA$

Maximale theoretische Spannung am Lautsprecher
$U_{s_{max}} = R_i * I_{s_{max}} = 8\ohm * 600mA = 4.8V$


Low-Pass Filter
Max Frequenz = 20khz 

$f_g = \frac{1}{2\pi RC}$
$C = \frac{1}{2\pi R f_g} = \frac{1}{2 \pi * 820\ohm * 20kHz} = 9.7nF \approx 10nF$

Backtracking
$f_g = \frac{1}{2\pi RC} = \frac{1}{2 \pi * 820\ohm * 10nF} = 19.4kHz$

R = $820\ohm$
F = $10nF$ r