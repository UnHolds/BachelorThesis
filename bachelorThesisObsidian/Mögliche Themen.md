
## I2C Lautsprecher-System

### Idee

Hier geht es darum ein System zu bauen das es erlaubt mehrer Lautsprecher an einen Master zu hängen. Wenn jedoch x viel Lautsprecher angehängt wurden ist der PullDown-Widerstand so groß, sodass das Signal nichtmehr richtig übertragen wird und alle Lautsprecher fallen aus.


### Schaltung

![[idea_i2c_speaker.svg|500]]

Die Slave Chips (voraussichtlich I2C DACs) haben alle auf der SDA Leitung einen zusätzlichen Pulldown-Widerstand. Weiters besitzt der Master einen Widerstand in Serie auf der SDA Leitung:

![[idea_i2c_speaker_real_conn.svg|400]]

Das bedeutet das wir Pulldown-Widerstände der Slaves in Serie hängen, was zur Folge hat das der Widerstand immer kleiner wird und somit mehr Strom aus dem Master "gezogen" wird. Die führt dann soweit das der Spannungspegel bei X vielen Slaves unter dem Schwellwert für HIGH liegt und somit die ganze Schaltung nichtmehr funktioniert.

Beispiel:
![[idea_i2c_speaker_resistor.svg|600]]

Im Beispiel oben ist gut zu erkennen, dass sich für den High-Pegel an den Slaves folgende Spannung einstellt.
$$U_{High Slave} = \frac{5V}{R + (R // R // R)} * (R // R // R)$$
(// = Parallel Schaltung)

Der Widerstand nach dem Master wird verwendet um eine Strombegrenzung einzuführen.#


## Metastabile NAND-Gatter

### Idee

Eine Schaltung bei der zwei NAND-Gatter parallel geschalten werden und alle Eingänge zusammen gehangen werden. Das Eingangssignal wird dann so gewählt, sodass ein NAND HIGH ausgibt und ein NAND LOW.

### Schaltung:

![[idea_nand.svg]]


Um die zwei verschiedenen Zustände zu erreichen können folgende Maßnahmen gesetzt werden:
* verschiedene Hersteller bei den NAND-Gatter
* Spannungsversorgung leicht anderst (z.B. 1. Gatter leichte Over-Voltage und 2. Gatter leichte Under-Voltage)

Der Signalerzeuger kann möglicherweise als DAC mit uC realisiert werden oder möglicherweise mit einem Counter Bausteil der je nach Signal hinunter oder hinauf zählt. Der aktuelle Zählerstand (parallel Ausgabe) könnte dann zum steueren eines DAC verwendet werden.

Beispiel:
![[idea_nand_signal_gen.svg|600]]