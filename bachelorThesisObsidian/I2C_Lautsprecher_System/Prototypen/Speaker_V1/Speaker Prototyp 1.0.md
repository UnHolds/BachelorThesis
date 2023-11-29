
### Steckbrett

![[Steckbrett_Prototyp_V1.jpg]]

### Schematic

![[Schematic_Prototyp_V1.JPG]]

### PCB

![[PCB_Prototyp_V1.JPG]]

### 3D-Render (Gehäuse + PCB)
![[3D_Render_Prototyp_V1.JPG]]


### Produziertes PCB

![[PCB_Front_Prototyp_V1.jpg]]

![[PCB_Back_Prototyp_V1.jpg]]

### Prototyp mit Gehäuse

![[Zusammenbau_1_Prototyp_V1.jpg]]

![[Zusammenbau_2_Prototyp_V1.jpg]]


### Tests

Für einen ersten Test wurde versucht, ein Lied über den Lautsprecher anzuspielen. Leider klang das Lied nicht richtig. Um mögliche Fehler zu finden, wird ein Sinus-Signal ausgegeben und das entstandene Signal mithilfe eines Mikrofons und FFT analysiert. 

| Parameter | Wert |
|----|------|
| Form | Sinus |
| Frequenz | 1000 Hz |

![[1kh_spectrum_10nF_ceramic.png|400]]


Hier ist gut zu erkennen, dass ein zweites Signal mit 504Hz vorhanden ist. Eine Überlegung war, dass dieses Signal durch Störungen im Kondensator (Keramik) entsteht. Um dies zu überprüfen, wird der Keramik-Kondensator mit einem Tantal-Kondensator ausgetauscht.

#### Ergebnis Tantal-Kondensator

![[1kh_spectrum_10nF_Tantal.png|400]]

Das Signal besitzt nun weniger Rauschen, jedoch ist die Störfrequenz bei ca. 500 Hz immer noch vorhanden.

#### Ergebnis

Nach weiteren Online-Nachforschungen und Besprechungen mit verschiedenen Personen, die im Elektronikbereich arbeiten, wurden mehrere Probleme festgestellt.

* Schaltung ist nicht stabil genug
* Große Verlustströme (geringe Effizienz)
* Mögliches Übersteuern
* Membran im Lautsprecher immer unter Spannung (nicht in Neutralstellung)

Aufgrund dieser Vielzahl an Problemen wurde eine neue Lösung erarbeitet. 

Für die neue Lösung wird der Verstärker überarbeitet und anstelle des [[2N3055.pdf|2N3055]] Transistors wird ein [[LM386.pdf|LM386]] oder ein [[LM4871.pdf|LM4871]] verwendet. Diese Chips ermöglichen eine effizientere Nutzung und stabileres Verhalten.