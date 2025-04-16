# Vårat elektronikprojekt!

Här kan vi skriva dokumentation om hur produkten används.

## Komponenter

* 1 Arduino mega
* 1 [ESP32-S3](https://www.electrokit.com/utvecklingskort-esp32-s3)
* 3 [Motordrivare](https://www.electrokit.com/stegmotordrivare-drv8825)
* 1 [RFID-läsare](https://www.electrokit.com/rfid-modul-med-tva-tags-13.56mhz)
* 1 [Nivåomvandlare](https://www.electrokit.com/nivaomvandlare-4-kanaler-bidirektionell)
* 1 Spännningsaggregat
* 1 100 $\mu$F kondensator

## Hur man sätter upp komponenterna

### Motordrivarna, arduinon, spänningsaggregatet & kondensatorn

<!-- ![Motordrivaren](images/motordrivare.png) -->
<img src="images/motordrivare.png" alt="motordrivaren" style="float: right;"/>

1. Koppla samman pin 6 och 7 på alla motordrivare.

2. Koppla samman pin 9 och 15 på alla motordrivare.

3. Koppla samman följande pins mellan motordrivarna.
    * 1
    * 2
    * 3
    * 4
    * 5
    * 8
    * 9
    * 16

4. sätt en kondensator mellan 15 V och Jord på spänningsaggrigatet.


5. Välj ut en av motordrivarna och koppla enligt följande mellan motordrivaren, arduinon och spänningsaggregatet.
    * Jord på spänningsaggregatet &rarr **GND**
    * Pin 1 &rarr **GP26**
    * Pin 2 &rarr **GP27**
    * Pin 3 &rarr **GP28**
    * Pin 4 &rarr **GP29**
    * Pin 5 &rarr **5V**
    * Pin 8 &rarr **GP25**
    * Pin 9 &rarr **GND**
    * Pin 16 &rarr 15 Volt på spänningsaggregatet

6. Koppla motordrivarna till motorerna enligt följande.
    * Pin 14 &rarr **Blå**
    * Pin 13 &rarr **Röd**
    * Pin 12 &rarr **Grön**
    * Pin 11 &rarr **Svart**

7. Välj ut vilken uppgift varje motordrivare har och koppla Pin 7 enligt följande.
    * Fyller skål 1 &rarr **GP22**
    * Fyller skål 2 &rarr **GP23**
    * Vrider skålarna &rarr **GP24**

### ESP32, nivåomvandlaren & arduinon

<img src="images/esp32.png" alt="motordrivaren" height="300pt" style="float: right;"/> 

<img src="images/levelshifter.png" alt="motordrivaren" height="300pt" style="float: right;"/>

#### Mellan Esp32 och nivåomvandlaren

* **GP9** &rarr **LV2** (SDA channel)
* **GP8** &rarr **LV4** (SCL channel)
* **GND** &rarr **GND** 

#### Mellan arduinon och nivåomvandlaren

* **5V** &rarr **HV**
* **3.3V** &rarr **LV**
* **GND** &rarr **GND**
* **GP20** &rarr **HV2** (SDA channel)
* **GP21** &rarr **HV4** (SCL channel)

### 

