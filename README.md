# Internet-radio
This project is about building a internet radio receiver which will chnge the audio output to analog, which will be transfered to old fm radio. From the radio will come audio to conncted speakers.
## Why?
I have old Aiwa, which can do only FM and AM frequency and most radio stations start to turn for DAB+ signal, so that's the reason, why I choose building the internet radio receiver. And I can listen to foreign countries radio stations.
## Technical specifications
It's charged by USB-C 16 pin connector(5V).
Than it's redukce to 3.3V by AMS1117. Most parts use 3.3V.
## Display
I choosed 2.5 inch TFT display.
## Buttons
I used cherry mx switches and rottary encoder.
1. resetovat button
2. sleep/on
3. up
4. down
5. encoder - volume up/ volume down 
6. encoder button - sound off
## Audio output
It's done by dac i12c chip and by 2 RCA cinches, which connects to AIWA.
## BOM 
1 ESP32 wroom (with Bluetooth and WIFI)
## License
This work is under GNU license. More info in license file.
## Schematics
I used kicad for that.
<img width="1154" height="786" alt="Snímek obrazovky 2026-08-17 105338" src="https://github.com/user-attachments/assets/a1a39087-8d16-4bc7-9614-82eba44727d7" />
## PCB Design
I used Kicad for that. Display will be conncted by cables that's why it is like it is.
<img width="918" height="792" alt="Snímek obrazovky 2026-08-31 152727" src="https://github.com/user-attachments/assets/8e8164eb-494c-4786-8286-402895675334" />
## 3d PCB renders
From Kicad. All other parts are on my fusion 360 3D model.
<img width="832" height="697" alt="Snímek obrazovky 2026-08-31 153812" src="https://github.com/user-attachments/assets/87534cd6-b521-4b95-bcd9-e2225ab4cdc1" />
<img width="617" height="622" alt="Snímek obrazovky 2026-08-31 153729" src="https://github.com/user-attachments/assets/8412b2f6-7363-4fba-85a4-0f400c2b847b" />


