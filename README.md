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
