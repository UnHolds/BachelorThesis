
### Steckbrett

![[I2C_Lautsprecher_System/Prototypen/Audio_Controller_V1/images/Steckbrett_Prototyp_V1.jpg]]

### Schematic

![[I2C_Lautsprecher_System/Prototypen/Audio_Controller_V1/images/Schematic_Prototyp_V1.JPG]]


### PCB

![[I2C_Lautsprecher_System/Prototypen/Audio_Controller_V1/images/PCB_Prototyp_V1.JPG]]


### 3D Model

![[3D_Model_Prototyp_V1.JPG]]


### Produziertes PCB

![[I2C_Lautsprecher_System/Prototypen/Audio_Controller_V1/images/PCB_Front_Prototyp_V1.jpg]]


![[I2C_Lautsprecher_System/Prototypen/Audio_Controller_V1/images/PCB_Back_Prototyp_V1.jpg]]


### Gelötete Platine

![[Soldered_Front_Prototyp_V1.jpg]]

![[Soldered_Back_Prototyp_V1.jpg]]


### Probleme

* VCC & GND vertauscht bei SD-Karte
* LEDs (D5, D6, D7, D8) mit nur Input-Pins verbunden.
* Loch für BNC-Stecker minimal zu klein (ca. 0.2mm)
* Sensor_VP & Sensor_VN können nicht für Input verwenden werden (Buttons), da der Crosstalk zwischen diesen Pins so groß ist, dass das Signal auf dem anderen Pin als HIGH erkannt wird.
* Header für das Auswählen, ob CS oder CS_X verwendet wird ist nicht gut, denn es könnte ein Kurzschluss entstehen (CS = HIGH; CS_X = LOW => wenn verbunden, dann Kurzschluss).

### Nice to have - nächster Prototyp

* Besserer Header für CS CS_X selector
* Header zum disconnected des 5V Pins der ESP32 Chips.
* Header-Pin für SDI-Load
* Labels für Testpoints