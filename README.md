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


## 3D Printing Settings

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


# Pinout & Connections

## 1. ILI9341 Display (U4)
| ILI9341 Display | ESP32 (U1) / Power | Note |
| :--- | :--- | :--- |
| **VCC** | +3.3V | Logic / Display Power |
| **GND** | GND | Ground |
| **CS** | **IO0** (DISP_CS) | Display Chip Select |
| **D/C** | **IO16** (D/C) | Data / Command |
| **MOSI** | **IO23** | SPI MOSI |
| **MISO** | **IO19** | SPI MISO |
| **SCK** | **IO18** | SPI Clock |
| **LED** | **IO17** (LED) | Backlight Control |
| **RESET** | **RESET** (via D/C / RESET network) | Display Reset |

---

## 2. Micro SD Card Slot (J2)
| Micro SD Slot | Power Source / ESP32 (U1) | Note |
| :--- | :--- | :--- |
| **VDD (Pin 4)** | +3.3V | SD Card Power |
| **GND (Pin 3, 6)** | GND | Ground |
| **DAT3/CD (Pin 2)** | **IO12** (SD_CS) / **IO5** | Chip Select (10kΩ pull-up R6) |
| **CMD (Pin 3)** | **IO23** | SPI MOSI |
| **CLK (Pin 5)** | **IO18** | SPI SCK |
| **DAT0 (Pin 7)** | **IO19** | SPI MISO (10kΩ pull-up R16) |
| **DAT1 (Pin 8)** | — | 10kΩ pull-up R17 to +3.3V |
| **DAT2 (Pin 1)** | — | 10kΩ pull-up R15 to +3.3V |

---

## 3. Audio DAC PCM5102 (U3)
| PCM5102 Pin | ESP32 (U1) / Power | Function / Note |
| :--- | :--- | :--- |
| **CPVDD, DVDD, AVDD** | +3.3V | DAC Power (filtered by C3, C4, C5) |
| **GND, AGND, DGND** | GND | Ground |
| **LRCK (Pin 15)** | **IO25** | I2S Word Select (LRCK) |
| **DIN (Pin 14)** | **IO27** | I2S Data Input |
| **BCK (Pin 13)** | **IO26** | I2S Bit Clock |
| **SCK (Pin 12)** | GND | System Clock (connected to GND) |
| **OUTL (Pin 6)** | C3 / R5 / J3A Output | Left Channel Audio Output (Coaxial J3A) |
| **OUTR (Pin 7)** | C1 / R4 / J3B Output | Right Channel Audio Output (Coaxial J3B) |

---

## 4. Rotary Encoder with Button (SW1)
| Encoder Pin | ESP32 (U1) / Power | Note |
| :--- | :--- | :--- |
| **A (Pin A)** | **IO32** | Encoder Phase A |
| **B (Pin B)** | **IO33** | Encoder Phase B |
| **C (Pin C)** | GND | Encoder Common Pin |
| **S1 (Pin S1)** | **IO18** | Encoder Switch / Button |
| **S2 (Pin S2)** | GND | Encoder Switch Other Side |

---

## 5. Control Buttons
| Button | ESP32 Pin | Connection |
| :--- | :--- | :--- |
| **SW2** | **IO23** / **IO5** | Pushbutton to GND (switches to GND) |
| **SW3** | **IO22** | Pushbutton to GND (switches to GND) |
| **SW5** | **IO15** (via 1kΩ R12) | Pushbutton to GND (switches to GND) |
| **SW6** | **EN** | RESET button (switches EN to GND) |
| **SW7** | **IO3 (RXD)** (via R8/R11) | User / Boot Button |

---

## 6. USB-C UART Converter (CP2102N - U5) & Power Supply
* **USB Connector (J1):** Supplies VBUS (+5V) to the **AMS1117-3.3 (U2)** regulator, which generates the main **+3.3V** power supply for the entire circuit.
* **Converter CP2102N (U5):**
  * **TXD (Pin 21)** $\rightarrow$ **IO3 (RXD)** on ESP32 (via 1kΩ resistor R11)
  * **RXD (Pin 20)** $\leftarrow$ **IO1 (TXD)** from ESP32 (via 1kΩ resistor R12)
  * **DTR / RTS** $\rightarrow$ Connected to **Q1/Q2 (BC847)** transistors for automatic programming mode switching (EN and IO0).

## Software & Firmware

The radio firmware is built on the **ESP32** platform (Arduino IDE / PlatformIO) and ensures smooth reception of internet streams via Wi-Fi, their decoding, and digital audio processing.

### Key Features
* **Wi-Fi Connectivity:** Automatic connection to the configured network at system startup.
* **Audio Streaming (I2S):** Direct digital audio data transmission over the I2S interface to the PCM5102 DAC for high sound quality.
* **Station Management:** Pre-configured playlist of domestic and foreign radio stations (MP3/AAC streams) with sequential switching.
* **Volume Control:** Fine digital volume control directly inside the audio decoder.

### Control Mapping
Control is handled via buttons and a rotary encoder connected to the ESP32 GPIO pins:
* **SW3 (BTN_UP):** Switch to the next radio station.
* **SW2 (BTN_DOWN):** Switch to the previous radio station.
* **SW5 (BTN_LEFT):** Volume down.
* **SW7 (BTN_RIGHT):** Volume up.
* **SW1 (Encoder):** Menu navigation and additional features.

### Included Libraries
* **WiFi.h** – Network connection and wireless management.
* **ESP32-audioI2S** – Audio decoding and I2S communication handling.

## Credits & Acknowledgments

* Firmware powered by **ESP32-audioI2S** and **WiFi.h** library.


## License

This work is under GNU license. More info in LICENSE file.
