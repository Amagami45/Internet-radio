#include <Arduino.h>
#include <WiFi.h>
#include <SPI.h>
#include <Preferences.h>
#include <TFT_eSPI.h>
#include <time.h>
#include "Audio.h"
#include "myprofile.h"

TFT_eSPI tft = TFT_eSPI();
Preferences prefs;


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
  "http://stream.nonstopoldies.at:8000/oldies",
  "http://icecast2.play.cz/cro-dvojka-128.mp3",
  "http://icecast2.play.cz/cro-vltava-128.mp3",
  "http://icecast2.play.cz/cro_radio-wave-128.mp3",
  "http://ice.abradio.cz/country128.mp3",
  "http://ice.abradio.cz/dechovka128.mp3",
  "http://ice.abradio.cz/classicfm128.mp3",
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
  "Nonstop Oldies",
  "Cro Dvojka",
  "Cro Vltava",
  "Radio Wave",
  "Country radio",
  "Radio dechovka",
  "Radio classic",
};

int currentStation = 0;
int maxStations = sizeof(stations) / sizeof(stations[0]);
int volume = 12; //(0 - 21)
bool isMuted = false;
unsigned long lastClockUpdate = 0;
unsigned long lastButtonPress = 0;

Audio audio;

void drawVolume(){
  tft.fillRect(10, 150, 220, 25, TFT_BLACK);
  tft.setCursor(10, 152);
  tft.setTextSize(2);

  if (isMuted) {
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.print("ZTLUMENO (MUTE)");
  } else{
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.print("Hlasitost: ");
    tft.print(volume);
    tft.print("/21");
  }
}

void updateClock() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo, 10)) {
    return;
  }
  char timeString[10];
  strftime(timeString, sizeof(timeString),"%H:%M:%S",&timeinfo);

  tft.setTextSize(2);
  tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
  tft.drawString(timeString, 210, 10);
}

void setup() {
  Serial.begin(115200);

  prefs.begin("radio", false);
  currentStation = prefs.getInt("station", 12);
  if(currentStation >= maxStations) currentStation = 0;

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  pinMode(ENCODER_BTN, INPUT_PULLUP);


  pinMode(BL_PIN, OUTPUT);
  digitalWrite(BL_PIN, HIGH);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setTextSize(3);
  tft.drawString("Internetove radio", 10, 10);


  WiFi.begin(ssid, password);
  Serial.print("Pripojovani k WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi pripojeno!");

  configTzTime("CET-1CEST,M3.5.0,M10.5.0/3","pool.ntp.org","tik.cesnet.cz");// This only works for Czechia Time

  tft.fillRect(10, 10, 310, 25, TFT_BLACK);
  tft.drawString("Web Radio", 10, 10);

  drawVolume();
  updateClock();


  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(volume);


  audio.connecttohost(stations[currentStation]);
  Serial.print("Hraje stanice: ");
  Serial.println(stationNames[currentStation]);
}

void loop() {

  audio.loop();
  if (millis() - lastClockUpdate >= 1000){
    lastClockUpdate = millis();
    updateClock();
  }

  if (millis() - lastButtonPress >= 200){

  if (digitalRead(BTN_UP) == LOW) { 
    lastButtonPress = millis();
    currentStation = (currentStation + 1) % maxStations;
    prefs.putInt("station", currentStation);
    audio.connecttohost(stations[currentStation]);
    Serial.print("Stanice: ");
    Serial.println(stationNames[currentStation]);
  }

  else if (digitalRead(BTN_DOWN) == LOW) { 
    lastButtonPress = millis();
    currentStation = (currentStation - 1 + maxStations) % maxStations;
    prefs.putInt("station", currentStation);
    audio.connecttohost(stations[currentStation]);
    Serial.print("Stanice: ");
    Serial.println(stationNames[currentStation]);
  }

  else if (digitalRead(BTN_LEFT) == LOW) {
    lastButtonPress = millis();
    isMuted = false;
    if (volume > 0) volume--;
    prefs.putInt("volume", volume);
    audio.setVolume(volume);
    Serial.print("Hlasitost: ");
    Serial.println(volume);
    drawVolume();
  }

  else if (digitalRead(BTN_RIGHT) == LOW) {
    lastButtonPress = millis();
    isMuted = false;
    if (volume < 21) volume++;
    prefs.putInt("volume", volume);
    audio.setVolume(volume);
    Serial.print("Hlasitost: ");
    Serial.println(volume);
    drawVolume();
  }
  else if(digitalRead(ENCODER_BTN) == LOW){
    lastButtonPress = millis();
    isMuted = !isMuted;
    audio.setVolume(isMuted ? 0 : volume);
    drawVolume();
  }
}
}


void audio_showstation(const char *info) {
  Serial.print("Stream info: ");
  Serial.println(info);

  tft.fillRect(10, 40, 300, 30, TFT_BLACK);
  tft.setCursor(10, 40);
  tft.setTextSize(3);
  tft.setTextColor(TFT_LIGHTGREEN, TFT_BLACK);
  tft.print(stationNames[currentStation]);
}

void audio_showstreamtitle(const char *info) {
  Serial.print("Hraje pisnicka: ");
  Serial.println(info);

  tft.fillRect(10, 80, 300, 60, TFT_BLACK);
  tft.setCursor(10, 80);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.print(info);
}