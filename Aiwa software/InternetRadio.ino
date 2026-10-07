#include <Arduino.h>
#include <WiFi.h>
#include "Audio.h"
#include "myprofile.h"


const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";


const char* stations[] = {

  "http://icecast3.play.cz/evropa2-128.mp3",
  "http://icecast1.play.cz/frekvence1-128.mp3",
  "http://icecast1.play.cz/impuls128.mp3",
  "http://ice.abradio.cz/kiss128.mp3",
  "http://icecast1.play.cz/radioblanik128.mp3",
  

  "http://ice.abradio.cz/radiozurnal128.mp3",
  "http://icecast7.play.cz/croplus128.mp3",
  

  "http://icecast1.play.cz/rockradio128.mp3",
  "http://icecast1.play.cz/beat128.mp3",
  

  "http://icecast1.play.cz/dance-radio128.mp3",
  "http://icecast1.play.cz/spin128.mp3",
  

  "http://ice.abradio.cz/fajn128.mp3",
  "http://icecast1.play.cz/crojazz128.mp3",
  

  "http://stream.srg-ssr.ch/m/rsj/mp3_128", 
  "http://stream.nonstopoldies.at:8000/oldies"
};

const char* stationNames[] = {
  "Evropa 2",
  "Frekvence 1",
  "Radio Impuls",
  "Radio Kiss",
  "Radio Blanik",
  "CRo Radiozurnal",
  "CRo Plus",
  "Rock Radio",
  "Radio Beat",
  "Dance Radio",
  "Radio Spin",
  "Fajn Radio",
  "CRo Jazz",
  "Swiss Jazz",
  "Nonstop Oldies"
};

int currentStation = 0;
int maxStations = sizeof(stations) / sizeof(stations[0]);
int volume = 12; //(0 - 21)

Audio audio;

void setup() {
  Serial.begin(115200);


  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  pinMode(ENCODER_BTN, INPUT_PULLUP);


  pinMode(BL_PIN, OUTPUT);
  digitalWrite(BL_PIN, HIGH);


  WiFi.begin(ssid, password);
  Serial.print("Pripojovani k WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi pripojeno!");


  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(volume);


  audio.connecttohost(stations[currentStation]);
  Serial.print("Hraje stanice: ");
  Serial.println(stationNames[currentStation]);
}

void loop() {

  audio.loop();


  if (digitalRead(BTN_UP) == LOW) { 
    delay(200); 
    currentStation = (currentStation + 1) % maxStations;
    audio.connecttohost(stations[currentStation]);
    Serial.print("Stanice: ");
    Serial.println(stationNames[currentStation]);
  }

  if (digitalRead(BTN_DOWN) == LOW) { 
    delay(200);
    currentStation = (currentStation - 1 + maxStations) % maxStations;
    audio.connecttohost(stations[currentStation]);
    Serial.print("Stanice: ");
    Serial.println(stationNames[currentStation]);
  }

  if (digitalRead(BTN_LEFT) == LOW) {
    delay(150);
    if (volume > 0) volume--;
    audio.setVolume(volume);
    Serial.print("Hlasitost: ");
    Serial.println(volume);
  }

  if (digitalRead(BTN_RIGHT) == LOW) {
    delay(150);
    if (volume < 21) volume++;
    audio.setVolume(volume);
    Serial.print("Hlasitost: ");
    Serial.println(volume);
  }
}


void audio_showstation(const char *info) {
  Serial.print("Stream info: ");
  Serial.println(info);
}

void audio_showstreamtitle(const char *info) {
  Serial.print("Hraje pisnicka: ");
  Serial.println(info);
}