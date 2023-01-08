
## I2C Lautsprecher-System

### Idee

Hier geht es darum, ein System zu bauen, das es erlaubt mehrere Lautsprecher an einen Master zu hängen. Wenn jedoch x viel Lautsprecher angehängt wurden, ist der Pulldown-Widerstand so groß, sodass das Signal nicht mehr richtig übertragen wird und alle Lautsprecher fallen aus.


### Schaltung

![[idea_i2c_speaker.svg#invert_W|500]]

Die Slave Chips (voraussichtlich I2C DACs) haben alle auf der SDA Leitung einen zusätzlichen Pulldown-Widerstand. Weiters besitzt der Master einen Widerstand in Serie auf der SDA Leitung:

![[idea_i2c_speaker_real_conn.svg#invert_W|400]]

Das bedeutet, dass wir Pulldown-Widerstände der Slaves in Serie hängen, was zur Folge hat, dass der Widerstand immer kleiner wird und somit mehr Strom aus dem Master "gezogen" wird. Die führt dann so weit, dass der Spannungspegel bei X vielen Slaves unter dem Schwellwert für HIGH liegt und somit die ganze Schaltung nicht mehr funktioniert.

Beispiel:
![[idea_i2c_speaker_resistor.svg#invert_W|600]]

Im Beispiel oben ist gut zu erkennen, dass sich für den High-Pegel an den Slaves folgende Spannung einstellt.
$$U_{High Slave} = \frac{5V}{R + (R // R // R)} * (R // R // R)$$
(// = Parallelschaltung)

Der Widerstand nach dem Master wird verwendet, um eine Strombegrenzung einzuführen.#


## Metastabile NAND-Gatter

### Idee

Eine Schaltung, bei der zwei NAND-Gatter parallel geschaltet werden und alle Eingänge zusammen gehangen werden. Das Eingangssignal wird dann so gewählt, sodass ein NAND HIGH ausgibt und ein NAND LOW.

### Schaltung:

![[idea_nand.svg#invert_W]]


Um die zwei verschiedenen Zustände zu erreichen, können folgende Maßnahmen gesetzt werden:
* verschiedene Hersteller bei den NAND-Gatter
* Spannungsversorgung leicht anders (z.B. 1. Gatter leichte Over-Voltage und 2. Gatter leichte Under-Voltage)

Der Signalerzeuger kann möglicherweise als DAC mit uC realisiert werden oder möglicherweise mit einem Counter Bauteil der je nach Signal hinunter oder hinauf zählt. Der aktuelle Zählerstand (parallel Ausgabe) könnte dann zum steuern eines DAC verwendet werden.

Beispiel:
![[idea_nand_signal_gen.svg#invert_W|600]]

### Aufbau 7400

![[idea_nand_internal.svg#invert_W|400]]
Quelle: https://project5474.org/index.php?title=7400_NS_443

## Programm-Abstraktionsfehler (Mikrocontroller)

### Idee

Eine Schaltung entwickeln, die als Steuerung für irgendetwas Visuelles dient. Der Programmcode des Mikrocontrollers führt dann zu einem "undefinierten" Verhalten. Dieses "undefinierte" Verhalten kann z.B. durch einen Integer-Overflow, Buffer-Overflow oder ähnlich erreicht werden. In diesem "undefinierten" Zustand verhält sich dann die Platine anders als erwartet. Eine mögliche Beispielplatine wäre eine Platine, die einen Raketenflug simuliert und in bestimmten Zuständen tritt dieser Fehler auf.


## SPI Slave Select Induction

### Idee

Eine Schaltung, welche die Slave Selects nicht mit LOW verbindet, sondern hochohmig lässt.
Neben der Slave Select Leitung wird dann eine weite Leitung geführt, welche das Potenzial via Induktion bestimmt. Damit die Slave Select Leitung die induzierte Spannung halten kann, wird ein Kondensator in diese Leitung verbaut. Der Kondensator wird aber nicht über einen gewöhnlichen Kondensator realisiert, sondern über die Kapazität zwischen den Leiterplatten.

### Schaltung

![[idea_spi_induction.svg#invert_W|600]]
Die Leitungen werden extra lang und nahe nebeneinander geführt, sodass der Cross-Talk maximiert wird. Auch die Leitungen für Leitungskapazität werden so gewählt, sodass auch diese maximiert werden. 

### Probleme

Ich kann mir gut vorstellen, dass dies so nicht möglich ist, da entweder die Leitungskapazität zu gering ist oder der Crosstalk nicht ausreicht.
Meiner Meinung nach handelt es sich hierbei auch um ein sehr konstruiertes Beispiel, welches so wahrscheinliche nie / sehr unwahrscheinlich auftreten wird.


## Zusammenfassung

Ich finde die ersten beiden Hardware-Überlegungen nicht schlecht (I2C Lautsprechern und NAND-Gatter), da diese einen Fehler aufzeigen, der passieren könnte. Natürlich müsste man sich noch überlegen, in welche größere Schaltung diese eingebracht werden können, sodass der "Effekt" noch glaubhafter ist. Das Mikrocontroller-Beispiel finde ich auch nicht so schlecht, nur ist bei diesem der Fehler nicht gut ersichtlich. (Kann z.B. nicht mit Oszilloskop gemessen werden).
Das letzte halte ich für sehr konstruiert und auch eher filigran sollte es funktionieren.