# Internet-radio

This project is about building an internet radio receiver which will change the audio output to analog, which will be transferred to an old FM radio (AIWA). From the radio, audio will come out to connected speakers.

## Why?

I have an old Aiwa, which can do only FM and AM frequencies, and most radio stations start to turn to DAB+ signal. So that's the main reason why I chose building this internet radio receiver. Also, I can listen to foreign countries' radio stations.

## Technical specifications

It's powered by a USB-C 16-pin connector (5V). Then it's reduced to 3.3V by AMS1117 regulator. Most parts use 3.3V logic.

### Display
* 2.8" SPI TFT display (ILI9341 controller, 240x320). Connected via cables to the PCB.

### Buttons & Controls
I used Cherry MX switches and a rotary encoder:
* Reset button
* Sleep / ON button
* Up button
* Down button
* Rotary encoder – Volume up / Volume down
* Rotary encoder button – Sound off (Mute)

### Audio output
It's done by PCM5102A DAC chip (I2S audio interface) and 2 RCA cinches (Stereo Left/Right), which connect directly to AIWA AUX input.

## BOM (Bill of Materials)

* ESP32-WROOM-32 (with Bluetooth and Wi-Fi)
* PCM5102A DAC board/chip
* 2.8" SPI TFT Display (ILI9341)
* USB-C 16-pin connector (Type-C)
* AMS1117 3.3V LDO regulator
* Dual horizontal RCA cinch connector
* Cherry MX mechanical switches
* Rotary encoder
* 0603 SMD capacitors and resistors

## Schematics & PCB Design

I used KiCad for that (2-layer board design). Display will be connected by cables, that's why it is designed like it is. 

<img width="918" height="792" alt="Snímek obrazovky 2026-08-31 152727" src="https://github.com/user-attachments/assets/8e8164eb-494c-4786-8286-402895675334" />
<img width="1154" height="786" alt="Snímek obrazovky 2026-08-17 105338" src="https://github.com/user-attachments/assets/a1a39087-8d16-4bc7-9614-82eba44727d7" />

## 3D PCB & Case Renders

* 3D PCB export (.STEP) is generated from KiCad.
* All other parts and enclosure case are modeled in Fusion 360.

<img width="832" height="697" alt="Snímek obrazovky 2026-08-31 153812" src="https://github.com/user-attachments/assets/87534cd6-b521-4b95-bcd9-e2225ab4cdc1" />
<img width="617" height="622" alt="Snímek obrazovky 2026-08-31 153729" src="https://github.com/user-attachments/assets/1abbabad-5c10-4fa3-9b09-0eca535af586" />
<img width="657" height="596" alt="Snímek obrazovky 2026-09-01 002420" src="https://github.com/user-attachments/assets/4481f678-9466-40c7-bc8f-cd3c85b9a40e" />


##  3D Printing Settings

* **Material:** PETG (recommended) or PLA
* **Layer Height:** 0.2 mm
* **Infill:** 15–20% (Gyroid or Grid)
* **Supports:** Needed only for RCA and USB-C cutouts on the rear panel

## Assembly Guide

### 1. PCB Assembly & Soldering
1. **SMD Components First:** Solder the small SMD parts first (AMS1117 regulator, 0603 capacitors/resistors, USB-C connector, and PCM5102A DAC).
2. **ESP32 Module:** Align and solder the ESP32-WROOM-32 module onto the board.
3. **Through-Hole Parts (THT):** Solder the Cherry MX switches, rotary encoder, and dual RCA cinch connector.

### 2. Display Wiring
* Connect the 2.8" ILI9341 TFT display to the PCB header using cables according to the KiCad schematic (VCC, GND, CS, RESET, DC, SDI/MOSI, SCK, LED).

### 3. Firmware Flashing
1. Connect the board to your PC via USB-C.
2. Flash **YoRadio** firmware using PlatformIO / Arduino IDE / Esptool.
3. Configure your GPIO pin mappings for the display, I2S DAC, rotary encoder, and Cherry MX buttons in `myoptions.h`.
4. Connect to the radio's Wi-Fi Access Point to set up your home Wi-Fi credentials and station playlist.

### 4. Enclosure Assembly
1. 3D print the case parts designed in Fusion 360.
2. Mount the 2.8" TFT display into the front panel slot.
3. Secure the PCB inside the main case using small M2/M3 screws.
4. Press keycaps onto the Cherry MX switches and attach the knob to the rotary encoder.
5. Close the 3D-printed enclosure.

### 5. Hooking up to AIWA
1. Connect an RCA stereo audio cable from the radio's cinch connectors to the **AUX / Line In** on your AIWA system.
2. Plug in a standard 5V USB-C power source.
3. Turn on AIWA, switch mode to AUX, select your favorite station, and enjoy!


# Zapojení komponent (Pinout & Connections)

## 1. Displej ILI9341 (U4)
| Displej ILI9341 | ESP32 (U1) / Napájení | Poznámka |
| :--- | :--- | :--- |
| **VCC** | +3.3V | Napájení logic/displeje |
| **GND** | GND | Zem |
| **CS** | **IO0** (DISP_CS) | Chip Select displeje |
| **D/C** | **IO16** (D/C) | Data / Command |
| **MOSI** | **IO23** | SPI MOSI |
| **MISO** | **IO19** | SPI MISO |
| **SCK** | **IO18** | SPI Hodiny |
| **LED** | **IO17** (LED) | Řízení podsvícení |
| **RESET** | **RESET** (přes D/C / RESET síť) | Reset displeje |

---

## 2. Micro SD Card Slot (J2)
| Micro SD Slot | Zdroj / ESP32 (U1) | Poznámka |
| :--- | :--- | :--- |
| **VDD (Pin 4)** | +3.3V | Napájení SD karty |
| **GND (Pin 3, 6)** | GND | Zem |
| **DAT3/CD (Pin 2)** | **IO12** (SD_CS) / **IO5** | Chip Select (pull-up R6 10kΩ) |
| **CMD (Pin 3)** | **IO23** | SPI MOSI |
| **CLK (Pin 5)** | **IO18** | SPI SCK |
| **DAT0 (Pin 7)** | **IO19** | SPI MISO (pull-up R16 10kΩ) |
| **DAT1 (Pin 8)** | — | Pull-up R17 (10kΩ) na +3.3V |
| **DAT2 (Pin 1)** | — | Pull-up R15 (10kΩ) na +3.3V |

---

## 3. Audio DAC PCM5102 (U3)
| PCM5102 Pin | ESP32 (U1) / Napájení | Funkce / Poznámka |
| :--- | :--- | :--- |
| **CPVDD, DVDD, AVDD** | +3.3V | Napájení DACu (filtrováno C3, C4, C5) |
| **GND, AGND, DGND** | GND | Zem |
| **LRCK (Pin 15)** | **IO25** | I2S Word Select (LRCK) |
| **DIN (Pin 14)** | **IO27** | I2S Data Input |
| **BCK (Pin 13)** | **IO26** | I2S Bit Clock |
| **SCK (Pin 12)** | GND | Systémové hodiny (propojeno na GND) |
| **OUTL (Pin 6)** | Výstup C3 / R5 / J3A | Audio výstup levý kanál (Coaxial J3A) |
| **OUTR (Pin 7)** | Výstup C1 / R4 / J3B | Audio výstup pravý kanál (Coaxial J3B) |

---

## 4. Rotační enkodér s tlačítkem (SW1)
| Enkodér Pin | ESP32 (U1) / Napájení | Poznámka |
| :--- | :--- | :--- |
| **A (Pin A)** | **IO32** | Fáze A enkodéru |
| **B (Pin B)** | **IO33** | Fáze B enkodéru |
| **C (Pin C)** | GND | Společný pin enkodéru |
| **S1 (Pin S1)** | **IO18** | Tlačítko enkodéru |
| **S2 (Pin S2)** | GND | Druhá strana tlačítka enkodéru |

---

## 5. Tlačítka (Control Buttons)
| Tlačítko | ESP32 Pin | Zapojení |
| :--- | :--- | :--- |
| **SW2** | **IO23** / **IO5** | Tlačítko na GND (spíná k GND) |
| **SW3** | **IO22** | Tlačítko na GND (spíná k GND) |
| **SW5** | **IO15** (přes R12 1kΩ) | Tlačítko na GND (spíná k GND) |
| **SW6** | **EN** | RESET tlačítko (spíná EN k GND) |
| **SW7** | **IO3 (RXD)** (přes R8/R11) | Uživatelské / boot tlačítko |

---

## 6. USB-C UART převodník (CP2102N - U5) & Napájení
* **USB konektor (J1):** Přivádí VBUS (+5V) do stabilizátoru **AMS1117-3.3 (U2)**, který vyrábí hlavní napájení **+3.3V** pro celý obvod.
* **Převodník CP2102N (U5):**
  * **TXD (Pin 21)** $\rightarrow$ **IO3 (RXD)** na ESP32 (přes rezistor R11 1kΩ)
  * **RXD (Pin 20)** $\leftarrow$ **IO1 (TXD)** z ESP32 (přes rezistor R12 1kΩ)
  * **DTR / RTS** $\rightarrow$ Připojeno na tranzistory **Q1/Q2 (BC847)** pro automatické přepínání do programovacího režimu (EN a IO0).
 
## Software a Firmware

Firmware rádia je postaven na platformě **ESP32** (Arduino IDE / PlatformIO) a zajišťuje plynulý příjem internetových streamů přes Wi-Fi, jejich dekódování a digitální zpracování zvuku[cite: 1, 2].

### Hlavní funkce
* **Wi-Fi konektivita:** Automatické připojení k definované síti při startu zařízení.
* **Audio streaming (I2S):** Přímé digitální vysílání audio dat přes I2S rozhraní do DAC převodníku PCM5102 pro vysokou kvalitu zvuku[cite: 1].
* **Správa stanic:** Přednastavený seznam českých i zahraničních rádiových stanic (MP3/AAC streamy) s možností cyklického přepínání[cite: 1].
* **Nastavení hlasitosti:** Jemné digitální řízení hlasitosti přímo v audio dekodéru.

### Mapování ovládacích prvků
Ovládání probíhá pomocí tlačítek a rotačního enkodéru propojených s GPIO piny ESP32[cite: 1]:
* **SW3 (BTN_UP):** Přepnutí na následující rádiovou stanici[cite: 1].
* **SW2 (BTN_DOWN):** Přepnutí na předchozí rádiovou stanici[cite: 1].
* **SW5 (BTN_LEFT):** Snížení hlasitosti[cite: 1].
* **SW7 (BTN_RIGHT):** Zvýšení hlasitosti[cite: 1].
* **SW1 (Enkodér):** Určeno pro navigaci v menu a doplňkové funkce[cite: 1].

### Použité knihovny
* **WiFi.h** – Správa bezdrátového připojení k síti.
* **ESP32-audioI2S** – Knihovna pro dekódování audia a obsluhu I2S komunikace.
## Credits & Acknowledgments

* Firmware powered by **ESP32-audioI2S** and **WiFi.h** library.


## License

This work is under GNU license. More info in LICENSE file.

