
Ein Problem mit der jetzigen Software ist, dass das Umschalten der CS Pins sehr langsam ist, im Bezug auf das Takt-Signal.

Hier eine Messung des Umschaltens, wenn das typische `digitalWrite` verwendet wird:

#### Code:
```c
void send(const uint8_t pins[], int numPins) {

	vspi->beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
	for(int i = 0; i < numPins; i++){
		digitalWrite(pins[i], LOW);
	}
	
	digitalWrite(vspi->pinSS(), LOW);
	uint16_t tdata = audio_buffer[current_buffer][audio_index] << 4;
	tdata |= ACTIVE;
	tdata &= MASK;
	vspi->transfer16(tdata);
	
	for(int i = 0; i < numPins; i++){
		digitalWrite(pins[i], HIGH);
	}
	
	digitalWrite(vspi->pinSS(), HIGH);
	vspi->endTransaction();
	audio_index++;
}
``` 


#### Messung:

Gesamte Zeit für die Übertragung: (`pins[] = {CS1, CS2, CS3, CS4, CS5}`)

![[Measurement_total_transfer_time_all_pins.png]]

Zeit: 7.56us

Zeitverzögerung CS Pin schalten (`pins[] = {CS1, CS2, CS3, CS4, CS5}`)

![[Measurement_switch_cs_until_transfer_all_pins.png]]

Time-Delay: 2.92us

Gesamte Zeit für die Übertragung: (`pins[] = {CS1}`)

![[Measurement_total_transfer_time_one_pin.png]]

Zeit: 6.06u.s

Zeitverzögerung CS Pin schalten (`pins[] = {CS1}`)

![[Measurement_switch_cs_until_transfer_one_pin.png]]

Time-Delay: 1.36us



### Berechnung

Die Frage stellt sich, ob mit dieser Übertragungsgeschwindigkeit 5 Ausgänge gleichzeitig beschalten werden können. Hierfür müssen alle Übertragungen innerhalb einer Sample-Zeit abgeschlossen sein. Daher ergibt die Formel $\frac{1}{Sample_Frequency}=\frac{1}{22050}=45.35us$. Wir wissen, dass eine Übertragung $6.06us/7.56us$ benötigt. und daher 5 Übertragungen $30.us/37.8us$. Dies würde sich Prinzipiell ausgehen, jedoch stellt sich die Frage, ob die Pins Zeit benötigen, bis sie wieder verwendet werden könne. Um dies herauszufinden, werden 2 Channels direkt hintereinander beschalten.


### Messung Multiplex

```c
uint8_t pins1[] = {CS1, CS2};
send(pins1 ,2);
uint8_t pins2[] = {CS3, CS4};
send(pins2 ,2);
```


![[Measurement_two_transfers_time_between_old.png]]

Zeit zwischen Übertragungen: 12.8us

Diese Zeit ensteht höchstwahrscheinlich durch `spi->beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));` und `vspi->endTransaction();` um dies zu verhindern könnte nur eine Transaktion für alle Kanäle verwendet werden.

### Verbesserung Zeit zwischen Übertragungen

#### Code:
```c
void send2(uint8_t** pins, uint8_t* numPins, uint8_t numChannel){
	vspi->beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
	digitalWrite(vspi->pinSS(), LOW);
	
	for(int channel = 0; channel < numChannel; channel++){
		for(int pin = 0; pin < numPins[channel]; pin++){
			digitalWrite(pins[channel][pin], LOW);
		}
		
		uint16_t tdata = audio_buffer[current_buffer][audio_index] << 4;
		tdata |= ACTIVE;
		tdata &= MASK;
		vspi->transfer16(tdata);
		
		for(int pin = 0; pin < numPins[channel]; pin++){
			digitalWrite(pins[channel][pin], HIGH);
		}
		
		audio_index++;
		update_audio_buffer_queue();
	}
	
	digitalWrite(vspi->pinSS(), HIGH);
	vspi->endTransaction();
}
```

#### Messung

![[Measurement_two_transfer_time_between_new.png]]



Diese neue Funktion erlaubt es nun 5 Kanäle gleichzeitig anzusteuern.

![[Measurement_five_signals_total_time.png]]

Total Time: 30.7us

Durch die obige Berechnung wissen wir, dass theoretisch ca. 45us zur Verfügung stehen. Wenn 30.7us für 5 Signale benötigt werden bedeutet, dass das maximal $\frac{45us}{\frac{30.7us}{5}}=7.32\approx7$ Signale übertragen werden können, bei einer Abtastrate von 22050Hz. Um dies noch ein bisschen zu verbessern, könnte die Frequenz des SPIs erhöht werden. Dies könnte jedoch zu einer instabilen Übertragung führen.